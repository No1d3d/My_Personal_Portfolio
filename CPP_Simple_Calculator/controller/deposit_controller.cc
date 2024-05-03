#include "deposit_controller.h"

namespace s21 {

DepositController::DepositController(DepositModelInterface* model)
    : model_(model) {}

void DepositController::SetDepositSum(double sum) {
  model_->SetDepositSum(sum);
}
void DepositController::SetDepositPeriod(int months) {
  model_->SetDepositPeriod(months);
}
void DepositController::SetDepositInterest(double interest) {
  model_->SetDepositInterest(interest);
}
void DepositController::SetDepositTax(double tax) {
  model_->SetDepositTax(tax);
}
void DepositController::SetDepositPeriodicityType(int type) {
  model_->SetDepositPeriodicityType(
      static_cast<IPaymentsPeriodicityDepositTypes>(type));
}
void DepositController::SetDepositCapitalization(bool capitalization) {
  model_->SetDepositCapitalization(capitalization);
}
void DepositController::SetDepositDateStart(int year, int month, int day) {
  model_->SetDepositDateStart(year, month, day);
}
void DepositController::AddDepositOperationReplenishment(int year, int month,
                                                         int day,
                                                         double amount) {
  model_->AddDepositOperationReplenishment(year, month, day, amount);
}
void DepositController::AddDepositOperationWithdrawal(int year, int month,
                                                      int day, double amount) {
  model_->AddDepositOperationWithdrawal(year, month, day, amount);
}
void DepositController::ClearDepositOperationsList() {
  model_->ClearDepositOperationsList();
}
void DepositController::CalculateDeposit() { model_->CalculateDeposit(); }

}  // namespace s21
