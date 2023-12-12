#ifndef S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_INTERFACE_H_

#include <string>

#include "math_model_public_interface.h"

namespace s21 {

class MathModelInterface : public MathModelPublicInterface {
 public:
  virtual ~MathModelInterface() = default;  // защищенный деструктор

  virtual void SetMathExpression(const std::string& new_expression) = 0;
  virtual void SetXValue(double x_value) = 0;
  virtual void MathExpressionAddString(const char* add) = 0;
  virtual void MathExpressionEraseEnd() = 0;

  virtual void CalculateX() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_MATH_MODEL_INTERFACE_H_