#include "math_controller.h"

namespace s21 {

MathController::MathController(MathModelInterface* model) : model_(model) {}

void MathController::SetMathExpression(const QString& str) {
  model_->SetMathExpression(str.toStdString());
}

void MathController::SetXValue(double x_value) { model_->SetXValue(x_value); }

void MathController::CalculateX() { model_->CalculateX(); }

void MathController::MathExpressionAddString(const char* add) {
  model_->MathExpressionAddString(add);
}

void MathController::MathExpressionEraseEnd() {
  model_->MathExpressionEraseEnd();
}

}  // namespace s21
