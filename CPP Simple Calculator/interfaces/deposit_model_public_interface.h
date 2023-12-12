#ifndef S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_PUBLIC_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_PUBLIC_INTERFACE_H_

#include "observer/observer_deposit_interfaces.h"

namespace s21 {

/**
 * @brief Периодичность выплат депозита
 */
enum IPaymentsPeriodicityDepositTypes {
  kPaymentsDay = 1,    // Выплаты каждый день
  kPaymentsMonth = 2,  // Выплаты раз в месяц
  kPaymentsEnd = 3,    // Выплаты в конце срока
};

class DepositModelPublicInterface {
 public:
  virtual ~DepositModelPublicInterface() = default;  // защищенный деструктор

  virtual double GetDepositInterestPayment() = 0;
  virtual double GetDepositTotalPayment() = 0;
  virtual double GetDepositTaxPayment() = 0;
  virtual bool IsDepositCalculated() = 0;
  virtual double GetDepositSum() = 0;
  virtual int GetDepositMonths() = 0;
  virtual double GetDepositInterest() = 0;
  virtual double GetDepositTax() = 0;
  virtual IPaymentsPeriodicityDepositTypes GetDepositPaymentsPeriodicity() = 0;
  virtual bool GetDepositCapitalizationType() = 0;

  virtual void RegisterObserver(DepositObserverUpdateInterface* object) = 0;
  virtual void RegisterObserver(DepositObserverErrorInterface* object) = 0;
  virtual void RemoveObserver(DepositObserverUpdateInterface* object) = 0;
  virtual void RemoveObserver(DepositObserverErrorInterface* object) = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_DEPOSIT_MODEL_PUBLIC_INTERFACE_H_