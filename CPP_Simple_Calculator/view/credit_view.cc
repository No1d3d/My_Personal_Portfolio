#include "credit_view.h"

#include <QMessageBox>

#include "../ui/ui_credit_view.h"
#include "view_helpers.h"

namespace s21 {

CreditView::CreditView(CreditControllerInterface *controller,
                       CreditModelPublicInterface *model, QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::CreditView),
      controller_(controller),
      model_(model) {
  ui_->setupUi(this);
  SetupCreditButtons();
  model_->RegisterObserver(static_cast<CreditObserverUpdateInterface *>(this));
  model_->RegisterObserver(static_cast<CreditObserverErrorInterface *>(this));
  ResetResult();
}

CreditView::~CreditView() { delete ui_; }

void CreditView::OnUpdate() {
  UpdateInputFieldsFromModel();
  UpdateResultFromModel();
}

void CreditView::OnError(const std::pair<std::string, std::string> &error) {
  UpdateResultFromModel();
  auto error_text = QString::fromStdString(error.second);
  if (error.first == "sum") {
    SetCreditSumError(error_text);
  } else if (error.first == "months") {
    SetCreditMonthsError(error_text);
  } else if (error.first == "interest") {
    SetCreditInterestError(error_text);
  } else {
    QMessageBox::critical(0, "Error", error_text);
  }
}

void CreditView::SetupCreditButtons() {
  // Слот для обработки "Рассчитать" в кредитном калькуляторе
  connect(ui_->credit_calculate_button, SIGNAL(clicked()), this,
          SLOT(HandleCreditButton()));
  // Слоты для обработки изменений в текстовых полях кредитного калькулятора
  connect(ui_->credit_sum_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleCreditSumChanged()));
  connect(ui_->credit_months_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleCreditMonthsChanged()));
  connect(ui_->credit_interest_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleCreditInterestChanged()));
}

void CreditView::UpdateInputFieldsFromModel() {
  // Обновляем данные для расчета по данным модели
  IPaymentsCreditTypes type = model_->GetCreditPaymentsType();

  if (type == kPaymentsDifferentiated) {
    ui_->payments_differentiated_radio->setChecked(true);
  } else {
    ui_->payments_annuity_radio->setChecked(true);
  }

  ui_->credit_sum_edit->setText(
      view_helpers::DoubleToQString(model_->GetCreditSum(), 2));

  int months = model_->GetCreditMonths();
  if (ui_->credit_period_box->currentIndex() == 1) {
    months = months / 12;
  }
  ui_->credit_months_edit->setText(QString::number(months));
  ui_->credit_interest_edit->setText(
      view_helpers::DoubleToQString(model_->GetCreditInterest(), 2));
}

void CreditView::UpdateResultFromModel() {
  // Обновляем результаты расчета по данным модели
  if (model_->IsCreditCalculated()) {
    double month_payment_min = model_->GetCreditPaymentMin();
    double month_payment_max = model_->GetCreditPaymentMax();
    double overpayment = model_->GetCreditOverpayment();
    double total = model_->GetCreditTotal();

    if (month_payment_min == month_payment_max) {
      ui_->credit_result_1->setText(QString::number(month_payment_min, 'f', 2));
    } else {
      ui_->credit_result_1->setText(QString::number(month_payment_max, 'f', 2) +
                                    "..." +
                                    QString::number(month_payment_min, 'f', 2));
    }
    ui_->credit_result_2->setText(QString::number(overpayment, 'f', 2));
    ui_->credit_result_3->setText(QString::number(total, 'f', 2));
  } else {
    ResetResult();
  }
}

void CreditView::ResetResult() {
  ui_->credit_result_1->setText("-");
  ui_->credit_result_2->setText("-");
  ui_->credit_result_3->setText("-");
}

void CreditView::SetCreditSumError(const QString &error_text) {
  ResetResult();
  ui_->credit_sum_edit->setStyleSheet("border: 1px solid red; color: red;");
  QMessageBox::critical(0, "Error", error_text);
}

void CreditView::SetCreditMonthsError(const QString &error_text) {
  ResetResult();
  ui_->credit_months_edit->setStyleSheet("border: 1px solid red; color: red;");
  QMessageBox::critical(0, "Error", error_text);
}

void CreditView::SetCreditInterestError(const QString &error_text) {
  ResetResult();
  ui_->credit_interest_edit->setStyleSheet(
      "border: 1px solid red; color: red;");
  QMessageBox::critical(0, "Error", error_text);
}

void CreditView::ResetCreditSumError() {
  ui_->credit_sum_edit->setStyleSheet("");
}

void CreditView::ResetCreditMonthsError() {
  ui_->credit_months_edit->setStyleSheet("");
}

void CreditView::ResetCreditInterestError() {
  ui_->credit_interest_edit->setStyleSheet("");
}

void CreditView::ResetAllErrors() {
  ResetCreditSumError();
  ResetCreditMonthsError();
  ResetCreditInterestError();
}

void CreditView::HandleCreditButton() {
  ResetAllErrors();

  bool input_correct;

  double sum =
      ui_->credit_sum_edit->text().replace(",", ".").toDouble(&input_correct);

  if (!input_correct) {
    SetCreditSumError(
        "Field \"Credit total sum (rub)\" contains incorrect values");
    return;
  }

  int months = ui_->credit_months_edit->text().toInt(&input_correct);

  if (!input_correct) {
    SetCreditMonthsError("Field \"Credit term\" contains incorrect values");
    return;
  }

  double interest =
      ui_->credit_interest_edit->text().replace(",", ".").toDouble(
          &input_correct);

  if (!input_correct) {
    SetCreditInterestError("Field \"Rate (%)\" contains incorrect values");
    return;
  }

  sum = QString::number(sum, 'f', 2).toDouble();
  interest = QString::number(interest, 'f', 2).toDouble();

  if (ui_->credit_period_box->currentIndex() == 1) {
    months = months * 12;
  }

  IPaymentsCreditTypes type;

  if (ui_->payments_differentiated_radio->isChecked()) {
    type = kPaymentsDifferentiated;
  } else {
    type = kPaymentsAnnuity;
  }

  controller_->SetCreditSum(sum);
  controller_->SetCreditMonths(months);
  controller_->SetCreditInterest(interest);
  controller_->SetCreditType(type);

  controller_->CalculateCredit();
}

void CreditView::HandleCreditSumChanged() { ResetCreditSumError(); }

void CreditView::HandleCreditMonthsChanged() { ResetCreditMonthsError(); }

void CreditView::HandleCreditInterestChanged() { ResetCreditInterestError(); }

}  // namespace s21