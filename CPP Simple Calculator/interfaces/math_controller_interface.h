#ifndef S21_SMART_CALC_V20_INTERFACES_MATH_CONTROLLER_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_MATH_CONTROLLER_INTERFACE_H_

#include <QString>

namespace s21 {

class MathControllerInterface {
 public:
  virtual ~MathControllerInterface() = default;  // защищенный деструктор

  virtual void SetMathExpression(const QString& str) = 0;
  virtual void SetXValue(double x_value) = 0;
  virtual void MathExpressionAddString(const char* add) = 0;
  virtual void MathExpressionEraseEnd() = 0;

  virtual void CalculateX() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_MATH_CONTROLLER_INTERFACE_H_