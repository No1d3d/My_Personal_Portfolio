#ifndef S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_INTERFACE_H_

#include "deposit_model_public_interface.h"

namespace s21 {

class DepositModelInterface : public DepositModelPublicInterface {
 public:
  virtual ~DepositModelInterface() = default;  // защищенный деструктор

  virtual void SetDepositSum(double sum) = 0;
  virtual void SetDepositPeriod(int months) = 0;
  virtual void SetDepositInterest(double interest) = 0;
  virtual void SetDepositTax(double tax) = 0;
  virtual void SetDepositPeriodicityType(
      IPaymentsPeriodicityDepositTypes type) = 0;
  virtual void SetDepositCapitalization(bool capitalization) = 0;
  virtual void SetDepositDateStart(int year, int month, int day) = 0;
  virtual void AddDepositOperationReplenishment(int year, int month, int day,
                                                double amount) = 0;
  virtual void AddDepositOperationWithdrawal(int year, int month, int day,
                                             double amount) = 0;

  virtual void ClearDepositOperationsList() = 0;
  virtual void CalculateDeposit() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_INTERFACE_H_