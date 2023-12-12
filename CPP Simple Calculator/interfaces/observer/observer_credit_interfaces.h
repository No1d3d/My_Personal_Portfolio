#ifndef S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_CREDIT_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_CREDIT_INTERFACE_H_

#include "observer_interface.h"

namespace s21 {

class CreditObserverUpdateInterface : public ObserverUpdateInterface {
 public:
  virtual ~CreditObserverUpdateInterface() = default;
};

class CreditObserverErrorInterface : public ObserverErrorInterface {
 public:
  virtual ~CreditObserverErrorInterface() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_CREDIT_INTERFACE_H_
