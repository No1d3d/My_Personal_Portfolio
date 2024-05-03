#ifndef S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_INTERFACE_H_

#include "credit_model_public_interface.h"

namespace s21 {

class CreditModelInterface : public CreditModelPublicInterface {
 public:
  virtual ~CreditModelInterface() = default;  // защищенный деструктор

  virtual void SetCreditSum(double sum) = 0;
  virtual void SetCreditMonths(int months) = 0;
  virtual void SetCreditInterest(double interest) = 0;
  virtual void SetCreditType(IPaymentsCreditTypes type) = 0;

  virtual void CalculateCredit() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_INTERFACE_H_