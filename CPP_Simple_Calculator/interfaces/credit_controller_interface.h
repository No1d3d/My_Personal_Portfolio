#ifndef S21_SMART_CALC_V20_INTERFACES_CREDIT_CONTROLLER_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_CREDIT_CONTROLLER_INTERFACE_H_

namespace s21 {

class CreditControllerInterface {
 public:
  virtual ~CreditControllerInterface() = default;  // защищенный деструктор

  virtual void SetCreditSum(double sum) = 0;
  virtual void SetCreditMonths(int months) = 0;
  virtual void SetCreditInterest(double interest) = 0;
  virtual void SetCreditType(int type) = 0;

  virtual void CalculateCredit() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_CREDIT_CONTROLLER_INTERFACE_H_