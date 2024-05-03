#include "credit_controller.h"

namespace s21 {

CreditController::CreditController(CreditModelInterface* model)
    : model_(model) {}

void CreditController::SetCreditSum(double sum) { model_->SetCreditSum(sum); }

void CreditController::SetCreditMonths(int months) {
  model_->SetCreditMonths(months);
}

void CreditController::SetCreditInterest(double interest) {
  model_->SetCreditInterest(interest);
}

void CreditController::SetCreditType(int type) {
  model_->SetCreditType(static_cast<IPaymentsCreditTypes>(type));
}

void CreditController::CalculateCredit() { model_->CalculateCredit(); }

}  // namespace s21
