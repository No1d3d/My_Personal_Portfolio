#include "deposit_view.h"

#include <QDateEdit>
#include <QMessageBox>

#include "../ui/ui_deposit_view.h"
#include "view_helpers.h"

namespace s21 {

DepositView::DepositView(DepositControllerInterface *controller,
                         DepositModelPublicInterface *model, QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::DepositView),
      controller_(controller),
      model_(model) {
  ui_->setupUi(this);
  view_helpers::SetupDateEdit(ui_->deposit_start_date_edit);
  ui_->deposit_periodicity_types_combo->setCurrentIndex(1);
  SetupDepositButtons();
  model_->RegisterObserver(static_cast<DepositObserverUpdateInterface *>(this));
  model_->RegisterObserver(static_cast<DepositObserverErrorInterface *>(this));
  ResetResult();
}

DepositView::~DepositView() { delete ui_; }

void DepositView::OnUpdate() {
  UpdateInputFieldsFromModel();
  UpdateResultFromModel();
}

void DepositView::OnError(const std::pair<std::string, std::string> &error) {
  UpdateResultFromModel();
  auto error_text = QString::fromStdString(error.second);
  if (error.first == "sum") {
    SetDepositSumError(error_text);
  } else if (error.first == "months") {
    SetDepositMonthsError(error_text);
  } else if (error.first == "interest") {
    SetDepositInterestError(error_text);
  } else if (error.first == "tax") {
    SetDepositTaxError(error_text);
  } else if (error.first == "date_start") {
    SetDepositDateStartError(error_text);
  } else if (error.first == "replenishment_date") {
    SetDepositAddMoneyError(error_text);
  } else if (error.first == "replenishment_sum") {
    SetDepositAddMoneyError(error_text);
  } else if (error.first == "withdrawal_date") {
    SetDepositSubMoneyError(error_text);
  } else if (error.first == "withdrawal_sum") {
    SetDepositSubMoneyError(error_text);
  } else {
    QMessageBox::critical(0, "Error", error_text);
  }
}

void DepositView::SetupDepositButtons() {
  // Слот для обработки "Рассчитать" в депозитном калькуляторе
  connect(ui_->deposit_calculate_button, SIGNAL(clicked()), this,
          SLOT(HandleDepositButton()));
  // Слоты для добавления и удаления строк в пополнениях/снятиях депозитного
  // калькулятора
  connect(ui_->addAddingButton, SIGNAL(clicked()), this,
          SLOT(AddOperationReplenishment()));
  connect(ui_->AddSubingButton, SIGNAL(clicked()), this,
          SLOT(AddOperationWithdrawal()));
  // Слоты для обработки изменений в текстовых полях депозитного калькулятора
  connect(ui_->deposit_sum_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleDepositSumChanged()));
  connect(ui_->deposit_months_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleDepositMonthsChanged()));
  connect(ui_->deposit_interest_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleDepositInterestChanged()));
  connect(ui_->deposit_tax_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleDepositTaxChanged()));
  connect(ui_->deposit_start_date_edit, SIGNAL(dateChanged(const QDate)), this,
          SLOT(HandleDepositDateStartChanged()));
}

void DepositView::UpdateInputFieldsFromModel() {
  // Обновляем данные для расчета по данным модели
  ui_->deposit_sum_edit->setText(
      view_helpers::DoubleToQString(model_->GetDepositSum(), 2));
  // QString::number(model_->GetDepositSum(), 'f', 2));

  int months = model_->GetDepositMonths();
  if (ui_->deposit_period_box->currentIndex() == 1) {
    months = months / 12;
  }

  ui_->deposit_months_edit->setText(QString::number(months));
  ui_->deposit_interest_edit->setText(
      view_helpers::DoubleToQString(model_->GetDepositInterest(), 2));
  // QString::number(model_->GetDepositInterest(), 'f', 2));
  ui_->deposit_tax_edit->setText(
      view_helpers::DoubleToQString(model_->GetDepositTax(), 2));
  // QString::number(model_->GetDepositTax(), 'f', 2));

  bool capitalization = model_->GetDepositCapitalizationType();

  if (capitalization == true) {
    ui_->deposit_capitalization_check_box->setChecked(true);
  } else {
    ui_->deposit_capitalization_check_box->setChecked(false);
  }

  IPaymentsPeriodicityDepositTypes type =
      model_->GetDepositPaymentsPeriodicity();

  if (type == kPaymentsDay) {
    ui_->deposit_periodicity_types_combo->setCurrentIndex(0);
  } else if (type == kPaymentsEnd) {
    ui_->deposit_periodicity_types_combo->setCurrentIndex(2);
  } else {
    ui_->deposit_periodicity_types_combo->setCurrentIndex(1);
  }
}

void DepositView::UpdateResultFromModel() {
  // Обновляем результаты расчета по данным модели
  if (model_->IsDepositCalculated()) {
    ui_->deposit_result_1->setText(
        QString::number(model_->GetDepositInterestPayment(), 'f', 2));
    ui_->deposit_result_2->setText(
        QString::number(model_->GetDepositTaxPayment(), 'f', 2));
    ui_->deposit_result_3->setText(
        QString::number(model_->GetDepositTotalPayment(), 'f', 2));
  } else {
    ResetResult();
  }
}

void DepositView::ResetResult() {
  ui_->deposit_result_1->setText("-");
  ui_->deposit_result_2->setText("-");
  ui_->deposit_result_3->setText("-");
}

bool DepositView::OperationsReplenishmentHandle() {
  for (int i = 0; i < ui_->deposit_add_money_layout->count(); i++) {
    bool input_add_money_correct;

    QHBoxLayout *line = qobject_cast<QHBoxLayout *>(
        ui_->deposit_add_money_layout->itemAt(i)->layout());
    QLineEdit *lineLineEdit =
        qobject_cast<QLineEdit *>(line->itemAt(0)->widget());
    QDateEdit *lineDateEdit =
        qobject_cast<QDateEdit *>(line->itemAt(1)->widget());

    int year =
        lineDateEdit->date().toString("yyyy").toInt(&input_add_money_correct);
    if (!input_add_money_correct) {
      SetDepositAddMoneyError(
          "Deposit replenishment date contains incorrect value!");
      return false;
    }

    int month =
        lineDateEdit->date().toString("MM").toInt(&input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositAddMoneyError(
          "Deposit replenishment date contains incorrect value!");
      return false;
    }

    int day =
        lineDateEdit->date().toString("dd").toInt(&input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositAddMoneyError(
          "Deposit replenishment date contains incorrect value!");
      return false;
    }

    double sum = lineLineEdit->text().replace(",", ".").toDouble(
        &input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositAddMoneyError(
          "Deposit replenishment sum contains incorrect value!");
      return false;
    }

    if (sum <= 0.0) {
      SetDepositAddMoneyError(
          "Deposit replenishment sum must be greater than 0!");
      return false;
    }

    sum = QString::number(sum, 'f', 2).toDouble();
    controller_->AddDepositOperationReplenishment(year, month, day, sum);
  }

  return true;
}

bool DepositView::OperationsWithdrawalHandle() {
  for (int i = 0; i < ui_->deposit_sub_money_layout->count(); i++) {
    bool input_add_money_correct;

    QHBoxLayout *line = qobject_cast<QHBoxLayout *>(
        ui_->deposit_sub_money_layout->itemAt(i)->layout());
    QLineEdit *lineLineEdit =
        qobject_cast<QLineEdit *>(line->itemAt(0)->widget());
    QDateEdit *lineDateEdit =
        qobject_cast<QDateEdit *>(line->itemAt(1)->widget());

    int year =
        lineDateEdit->date().toString("yyyy").toInt(&input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositSubMoneyError(
          "Deposit withdrawal date contains incorrect value!");
      return false;
    }

    int month =
        lineDateEdit->date().toString("MM").toInt(&input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositSubMoneyError(
          "Deposit withdrawal date contains incorrect value!");
      return false;
    }

    int day =
        lineDateEdit->date().toString("dd").toInt(&input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositSubMoneyError(
          "Deposit withdrawal date contains incorrect value!");
      return false;
    }

    double sum = lineLineEdit->text().replace(",", ".").toDouble(
        &input_add_money_correct);

    if (!input_add_money_correct) {
      SetDepositSubMoneyError(
          "Deposit withdrawal sum contains incorrect value!");
      return false;
    }

    if (sum <= 0.0) {
      SetDepositSubMoneyError("Deposit withdrawal sum must be greater than 0!");
      return false;
    }

    sum = QString::number(sum, 'f', 2).toDouble();
    controller_->AddDepositOperationWithdrawal(year, month, day, sum);
  }

  return true;
}

void DepositView::AddOperationLine(QBoxLayout *layout) {
  QHBoxLayout *line = new QHBoxLayout;

  line->addWidget(new QLineEdit);
  QDateEdit *dateEdit = new QDateEdit;
  view_helpers::SetupDateEdit(dateEdit);
  line->addWidget(dateEdit);
  QPushButton *button = new QPushButton;
  QPixmap pix(":/images/delete.png");
  QIcon icon(pix);
  button->resize(QSize(25, 25));
  button->setIcon(icon);
  button->setIconSize(QSize(16, 16));
  line->addWidget(button);

  layout->addLayout(line);

  connect(button, SIGNAL(clicked()), this, SLOT(DeleteOperationLine()));
}

void DepositView::SetDepositSumError(const QString &error_text) {
  ResetResult();
  ui_->deposit_sum_edit->setStyleSheet("border: 1px solid red; color: red;");
  ui_->deposit_sum_edit->setFocus();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositMonthsError(const QString &error_text) {
  ResetResult();
  ui_->deposit_months_edit->setStyleSheet("border: 1px solid red; color: red;");
  ui_->deposit_months_edit->setFocus();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositInterestError(const QString &error_text) {
  ResetResult();
  ui_->deposit_interest_edit->setStyleSheet(
      "border: 1px solid red; color: red;");
  ui_->deposit_interest_edit->setFocus();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositTaxError(const QString &error_text) {
  ResetResult();
  ui_->deposit_tax_edit->setStyleSheet("border: 1px solid red; color: red;");
  ui_->deposit_tax_edit->setFocus();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositDateStartError(const QString &error_text) {
  ResetResult();
  ui_->deposit_start_date_edit->setStyleSheet(
      "border: 1px solid red; color: red;");
  ui_->deposit_start_date_edit->setFocus();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositAddMoneyError(const QString &error_text) {
  ResetResult();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::SetDepositSubMoneyError(const QString &error_text) {
  ResetResult();
  QMessageBox::critical(0, "Error", error_text);
}

void DepositView::ResetDepositSumError() {
  ui_->deposit_sum_edit->setStyleSheet("");
}

void DepositView::ResetDepositMonthsError() {
  ui_->deposit_months_edit->setStyleSheet("");
}

void DepositView::ResetDepositInterestError() {
  ui_->deposit_interest_edit->setStyleSheet("");
}

void DepositView::ResetDepositTaxError() {
  ui_->deposit_tax_edit->setStyleSheet("");
}

void DepositView::ResetDepositDateStartError() {
  ui_->deposit_start_date_edit->setStyleSheet("");
}

void DepositView::ResetAllErrors() {
  ResetDepositSumError();
  ResetDepositMonthsError();
  ResetDepositInterestError();
  ResetDepositTaxError();
  ResetDepositDateStartError();
}

void DepositView::HandleDepositButton() {
  ResetAllErrors();

  bool input_correct;

  double sum =
      ui_->deposit_sum_edit->text().replace(",", ".").toDouble(&input_correct);
  if (!input_correct) {
    SetDepositSumError("Field \"Deposit sum\" contains incorrect value!");
    return;
  }

  int months = ui_->deposit_months_edit->text().toInt(&input_correct);
  if (!input_correct) {
    SetDepositMonthsError("Field \"Deposit period\" contains incorrect value!");
    return;
  }

  double interest =
      ui_->deposit_interest_edit->text().replace(",", ".").toDouble(
          &input_correct);
  if (!input_correct) {
    SetDepositInterestError(
        "Field \"Deposit percent rate\" contains incorrect value!");
    return;
  }

  double tax =
      ui_->deposit_tax_edit->text().replace(",", ".").toDouble(&input_correct);
  if (!input_correct) {
    SetDepositTaxError("Field \"Deposit tax rate\" contains incorrect value!");
    return;
  }

  int deposit_year =
      ui_->deposit_start_date_edit->date().toString("yyyy").toInt(
          &input_correct);
  if (!input_correct) {
    SetDepositDateStartError(
        "Field \"Deposit placement date\" contains incorrect value!");
    return;
  }

  int deposit_month =
      ui_->deposit_start_date_edit->date().toString("MM").toInt(&input_correct);
  if (!input_correct) {
    SetDepositDateStartError(
        "Field \"Deposit placement date\" contains incorrect value!");
    return;
  }

  int deposit_day =
      ui_->deposit_start_date_edit->date().toString("dd").toInt(&input_correct);
  if (!input_correct) {
    SetDepositDateStartError(
        "Field \"Deposit placement date\" contains incorrect value!");
    return;
  }

  IPaymentsPeriodicityDepositTypes periodicity_type;
  bool capitalization_type;

  if (ui_->deposit_period_box->currentIndex() == 1) {
    months = months * 12;
  }

  if (ui_->deposit_periodicity_types_combo->currentIndex() == 0) {
    periodicity_type = kPaymentsDay;
  } else if (ui_->deposit_periodicity_types_combo->currentIndex() == 2) {
    periodicity_type = kPaymentsEnd;
  } else {
    periodicity_type = kPaymentsMonth;
  }

  if (ui_->deposit_capitalization_check_box->isChecked()) {
    capitalization_type = true;
  } else {
    capitalization_type = false;
  }

  controller_->ClearDepositOperationsList();

  bool success = OperationsReplenishmentHandle();
  if (success) {
    success = OperationsWithdrawalHandle();
  }

  if (!success) {
    return;
  }

  sum = QString::number(sum, 'f', 2).toDouble();
  months = QString::number(months, 'f', 2).toDouble();
  interest = QString::number(interest, 'f', 2).toDouble();
  tax = QString::number(tax, 'f', 2).toDouble();

  controller_->SetDepositSum(sum);
  controller_->SetDepositPeriod(months);
  controller_->SetDepositInterest(interest);
  controller_->SetDepositTax(tax);
  controller_->SetDepositPeriodicityType(periodicity_type);
  controller_->SetDepositCapitalization(capitalization_type);
  controller_->SetDepositDateStart(deposit_year, deposit_month, deposit_day);
  controller_->CalculateDeposit();
}

void DepositView::AddOperationReplenishment() {
  AddOperationLine(ui_->deposit_add_money_layout);
}

void DepositView::AddOperationWithdrawal() {
  AddOperationLine(ui_->deposit_sub_money_layout);
}

void DepositView::DeleteOperationLine() {
  QPushButton *delete_button = qobject_cast<QPushButton *>(sender());

  QHBoxLayout *line = qobject_cast<QHBoxLayout *>(
      view_helpers::FindParentLayout(delete_button));

  QLineEdit *deleted_line_edit =
      qobject_cast<QLineEdit *>(line->itemAt(0)->widget());
  QDateEdit *deleted_line_date =
      qobject_cast<QDateEdit *>(line->itemAt(1)->widget());

  delete_button->hide();
  deleted_line_edit->hide();
  deleted_line_date->hide();

  delete delete_button;
  delete deleted_line_edit;
  delete deleted_line_date;
  delete line;
}

void DepositView::HandleDepositSumChanged() { ResetDepositSumError(); }

void DepositView::HandleDepositMonthsChanged() { ResetDepositMonthsError(); }

void DepositView::HandleDepositInterestChanged() {
  ResetDepositInterestError();
}

void DepositView::HandleDepositTaxChanged() { ResetDepositTaxError(); }

void DepositView::HandleDepositDateStartChanged() {
  ResetDepositDateStartError();
}

}  // namespace s21