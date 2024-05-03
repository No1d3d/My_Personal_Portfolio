#include "math_view.h"

#include <QMessageBox>

#include "../ui/ui_math_view.h"
#include "view_helpers.h"

namespace s21 {

MathView::MathView(MathControllerInterface* controller,
                   MathModelPublicInterface* model, GraphView* graph_view,
                   QWidget* parent)
    : QWidget(parent),
      ui_(new Ui::MathView),
      controller_(controller),
      model_(model),
      graph_view_(graph_view) {
  ui_->setupUi(this);
  graph_view_->setParent(this);
  graph_view_->setWindowFlags(Qt::Window);
  SetupButtons();
  model_->RegisterObserver(static_cast<MathObserverUpdateInterface*>(this));
  model_->RegisterObserver(static_cast<MathObserverErrorInterface*>(this));
}

MathView::~MathView() {
  model_->RemoveObserver(static_cast<MathObserverUpdateInterface*>(this));
  model_->RemoveObserver(static_cast<MathObserverErrorInterface*>(this));
  delete ui_;
}

void MathView::OnUpdate() {
  ui_->src_input->setPlainText(
      QString::fromStdString(model_->GetMathExpression()));
  if (model_->IsMathCalculated()) {
    ui_->x_edit->setText(view_helpers::DoubleToQString(model_->GetXValue(), 7));
    SetCalcResult(model_->GetMathResult());
  } else {
    SetCalcResult("");
  }

  ui_->src_input->setFocus();
  QTextCursor cursor = ui_->src_input->textCursor();
  cursor.movePosition(QTextCursor::End);
  ui_->src_input->setTextCursor(cursor);
}

void MathView::OnError(const std::pair<std::string, std::string>& error) {
  auto error_text = QString::fromStdString(error.second);
  if (error.first == "input") {
    SetInputValueError(error_text);
  } else if (error.first == "wrong_operator") {
    QMessageBox::critical(0, "Error", error_text);
  } else if (error.first == "graph_calculation") {
    SetInputValueError(error_text);
  } else {
    QMessageBox::critical(0, "Unexpected Error", error_text);
  }
}

void MathView::SetupButtons() {
  connect(ui_->calc_button, SIGNAL(clicked()), this, SLOT(HandleCalcButton()));
  connect(ui_->graph_button, SIGNAL(clicked()), this,
          SLOT(HandleGraphButton()));
  connect(ui_->mod_button, SIGNAL(clicked()), this, SLOT(HandleButtonMod()));
  connect(ui_->div_button, SIGNAL(clicked()), this, SLOT(HandleButtonDiv()));
  connect(ui_->mul_button, SIGNAL(clicked()), this, SLOT(HandleButtonMul()));
  connect(ui_->sub_button, SIGNAL(clicked()), this, SLOT(HandleButtonSub()));
  connect(ui_->add_button, SIGNAL(clicked()), this, SLOT(HandleButtonAdd()));
  connect(ui_->clear_button, SIGNAL(clicked()), this,
          SLOT(HandleClearButton()));
  connect(ui_->lbracket_button, SIGNAL(clicked()), this,
          SLOT(HandleButtonLBracket()));
  connect(ui_->rbracket_button, SIGNAL(clicked()), this,
          SLOT(HandleButtonRBracket()));
  connect(ui_->pow_button, SIGNAL(clicked()), this, SLOT(HandleButtonPow()));
  connect(ui_->cos_button, SIGNAL(clicked()), this, SLOT(HandleButtonCos()));
  connect(ui_->sin_button, SIGNAL(clicked()), this, SLOT(HandleButtonSin()));
  connect(ui_->tan_button, SIGNAL(clicked()), this, SLOT(HandleButtonTan()));
  connect(ui_->sqrt_button, SIGNAL(clicked()), this, SLOT(HandleButtonSqrt()));
  connect(ui_->acos_button, SIGNAL(clicked()), this, SLOT(HandleButtonAcos()));
  connect(ui_->atan_button, SIGNAL(clicked()), this, SLOT(HandleButtonAtan()));
  connect(ui_->asin_button, SIGNAL(clicked()), this, SLOT(HandleButtonAsin()));
  connect(ui_->ln_button, SIGNAL(clicked()), this, SLOT(HandleButtonLn()));
  connect(ui_->pi_button, SIGNAL(clicked()), this, SLOT(HandleButtonPi()));
  connect(ui_->e_button, SIGNAL(clicked()), this, SLOT(HandleButtonE()));
  connect(ui_->x_button, SIGNAL(clicked()), this, SLOT(HandleButtonX()));
  connect(ui_->log_button, SIGNAL(clicked()), this, SLOT(HandleButtonLog()));
  connect(ui_->num7_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum7()));
  connect(ui_->num8_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum8()));
  connect(ui_->num9_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum9()));
  connect(ui_->num4_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum4()));
  connect(ui_->num5_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum5()));
  connect(ui_->num6_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum6()));
  connect(ui_->num1_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum1()));
  connect(ui_->num2_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum2()));
  connect(ui_->num3_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum3()));
  connect(ui_->num0_button, SIGNAL(clicked()), this, SLOT(HandleButtonNum0()));
  connect(ui_->unary_minus_button, SIGNAL(clicked()), this,
          SLOT(HandleButtonUnaryMinus()));
  connect(ui_->point_button, SIGNAL(clicked()), this,
          SLOT(HandlePointButton()));
  connect(ui_->backspace_button, SIGNAL(clicked()), this,
          SLOT(HandleBackspaceButton()));
  connect(ui_->x_edit, SIGNAL(textChanged(QString)), this,
          SLOT(HandleXEditChanged()));
  connect(ui_->src_input, SIGNAL(textChanged()), this,
          SLOT(HandleInputChanged()));
}

QString MathView::GetViewMathExpression() {
  return ui_->src_input->toPlainText().remove('\n');
}

void MathView::SetCalcResult(double result) {
  ui_->result_edit->setText(view_helpers::DoubleToQString(result, 7));
}

void MathView::SetCalcResult(const QString& result) {
  ui_->result_edit->setText(result);
}

void MathView::SetXValueError(const QString& error_text) {
  SetCalcResult("ERROR");
  ui_->x_edit->setStyleSheet("border: 1px solid red; color: red;");
  QMessageBox::critical(0, "Error", error_text);
}

void MathView::SetInputValueError(const QString& error_text) {
  SetCalcResult("ERROR");
  ui_->src_input->setStyleSheet("border: 1px solid red; color: red;");
  QMessageBox::critical(0, "Error", error_text);
}

void MathView::ResetXValueError() { ui_->x_edit->setStyleSheet(""); }

void MathView::ResetInputValueError() { ui_->src_input->setStyleSheet(""); }

void MathView::ResetAllErrors() {
  ResetXValueError();
  ResetInputValueError();
}

void MathView::HandleCalcButton() {
  ResetAllErrors();

  bool x_convert_ok;
  double x_value =
      ui_->x_edit->text().replace(",", ".").toDouble(&x_convert_ok);
  x_value = QString::number(x_value, 'f', 7).toDouble();

  controller_->SetMathExpression(GetViewMathExpression());

  if (x_convert_ok == true) {
    controller_->SetXValue(x_value);
    controller_->CalculateX();
  } else {
    SetXValueError("Field \"x =\" contains incorrect value!");
  }

  if (graph_view_->isVisible()) {
    graph_view_->UpdateGraphWindow(GetViewMathExpression());
  }
}

void MathView::HandleGraphButton() {
  controller_->SetMathExpression(GetViewMathExpression());
  graph_view_->UpdateGraphWindow(GetViewMathExpression());
}

void MathView::HandleClearButton() { ui_->src_input->clear(); }

void MathView::HandlePointButton() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString(".");
}

void MathView::HandleBackspaceButton() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionEraseEnd();
}

void MathView::HandleButtonMod() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("mod");
}

void MathView::HandleButtonDiv() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("/");
}

void MathView::HandleButtonMul() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("*");
}

void MathView::HandleButtonSub() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("-");
}
void MathView::HandleButtonAdd() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("+");
}

void MathView::HandleButtonLBracket() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("(");
}

void MathView::HandleButtonRBracket() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString(")");
}

void MathView::HandleButtonPow() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("^");
}

void MathView::HandleButtonCos() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("cos");
}

void MathView::HandleButtonSin() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("sin");
}

void MathView::HandleButtonTan() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("tan");
}

void MathView::HandleButtonSqrt() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("sqrt");
}

void MathView::HandleButtonAcos() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("acos");
}

void MathView::HandleButtonAtan() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("atan");
}

void MathView::HandleButtonAsin() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("asin");
}

void MathView::HandleButtonLn() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("ln");
}

void MathView::HandleButtonPi() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("pi");
}

void MathView::HandleButtonE() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("e");
}

void MathView::HandleButtonX() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("x");
}

void MathView::HandleButtonLog() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("log");
}

void MathView::HandleButtonNum0() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("0");
}

void MathView::HandleButtonNum1() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("1");
}

void MathView::HandleButtonNum2() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("2");
}

void MathView::HandleButtonNum3() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("3");
}

void MathView::HandleButtonNum4() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("4");
}

void MathView::HandleButtonNum5() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("5");
}

void MathView::HandleButtonNum6() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("6");
}

void MathView::HandleButtonNum7() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("7");
}

void MathView::HandleButtonNum8() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("8");
}

void MathView::HandleButtonNum9() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("9");
}

void MathView::HandleButtonUnaryMinus() {
  controller_->SetMathExpression(GetViewMathExpression());
  controller_->MathExpressionAddString("~");
}

void MathView::HandleXEditChanged() { ResetXValueError(); }

void MathView::HandleInputChanged() {
  ResetInputValueError();
  SetCalcResult("");
}

}  // namespace s21