#ifndef S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_PUBLIC_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_PUBLIC_INTERFACE_H_

#include "observer/observer_credit_interfaces.h"

namespace s21 {

/**
 * @brief Способы начисления процентов кредита
 */
enum IPaymentsCreditTypes {
  kPaymentsAnnuity = 1,  // Аннуитетный график платежей
  kPaymentsDifferentiated = 2,  // Дифференцированный график платежей
};

class CreditModelPublicInterface {
 public:
  virtual ~CreditModelPublicInterface() = default;  // защищенный деструктор

  virtual double GetCreditSum() = 0;
  virtual int GetCreditMonths() = 0;
  virtual double GetCreditInterest() = 0;
  virtual IPaymentsCreditTypes GetCreditPaymentsType() = 0;
  virtual double GetCreditPaymentMin() = 0;
  virtual double GetCreditPaymentMax() = 0;
  virtual double GetCreditOverpayment() = 0;
  virtual double GetCreditTotal() = 0;
  virtual bool IsCreditCalculated() = 0;

  virtual void RegisterObserver(CreditObserverUpdateInterface* object) = 0;
  virtual void RegisterObserver(CreditObserverErrorInterface* object) = 0;
  virtual void RemoveObserver(CreditObserverUpdateInterface* object) = 0;
  virtual void RemoveObserver(CreditObserverErrorInterface* object) = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_CREDIT_MODEL_PUBLIC_INTERFACE_H_