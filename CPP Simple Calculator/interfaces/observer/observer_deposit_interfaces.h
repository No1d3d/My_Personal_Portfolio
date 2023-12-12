#ifndef S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_DEPOSIT_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_DEPOSIT_INTERFACE_H_

#include "observer_interface.h"

namespace s21 {

class DepositObserverUpdateInterface : public ObserverUpdateInterface {
 public:
  virtual ~DepositObserverUpdateInterface() = default;
};

class DepositObserverErrorInterface : public ObserverErrorInterface {
 public:
  virtual ~DepositObserverErrorInterface() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_DEPOSIT_INTERFACE_H_
