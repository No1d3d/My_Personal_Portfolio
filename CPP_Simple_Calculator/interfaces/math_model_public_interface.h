#ifndef S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_PUBLIC_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_PUBLIC_INTERFACE_H_

#include <string>

#include "observer/observer_math_interfaces.h"

namespace s21 {

class MathModelPublicInterface {
 public:
  virtual ~MathModelPublicInterface() = default;  // защищенный деструктор

  virtual double GetMathResult() = 0;
  virtual double GetXValue() = 0;
  virtual std::string GetMathExpression() = 0;
  virtual bool IsMathCalculated() = 0;

  virtual void RegisterObserver(MathObserverUpdateInterface* object) = 0;
  virtual void RegisterObserver(MathObserverErrorInterface* object) = 0;
  virtual void RemoveObserver(MathObserverUpdateInterface* object) = 0;
  virtual void RemoveObserver(MathObserverErrorInterface* object) = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_PUBLIC_INTERFACE_H_