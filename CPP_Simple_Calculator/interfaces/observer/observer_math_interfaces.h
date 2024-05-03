#ifndef S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_MATH_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_MATH_INTERFACE_H_

#include "observer_interface.h"

namespace s21 {

class MathObserverUpdateInterface : public ObserverUpdateInterface {
 public:
  virtual ~MathObserverUpdateInterface() = default;
};

class MathObserverErrorInterface : public ObserverErrorInterface {
 public:
  virtual ~MathObserverErrorInterface() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_MATH_INTERFACE_H_
