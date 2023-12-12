#ifndef S21_SMART_CALC_V20_CONTROLLER_MATH_CONTROLLER_H_
#define S21_SMART_CALC_V20_CONTROLLER_MATH_CONTROLLER_H_

#include <QString>

#include "../interfaces/math_controller_interface.h"
#include "../interfaces/math_model_interface.h"

namespace s21 {

class MathController final : public MathControllerInterface {
 public:
  MathController() = delete;
  explicit MathController(MathModelInterface* model);
  MathController(const MathController& other) = delete;
  MathController(MathController&& other) = delete;
  MathController& operator=(const MathController& other) = delete;
  MathController& operator=(MathController&& other) = delete;
  ~MathController() = default;

  void SetMathExpression(const QString& str) override;
  void SetXValue(double x_value) override;
  void CalculateX() override;
  void MathExpressionAddString(const char* add) override;
  void MathExpressionEraseEnd() override;

 private:
  MathModelInterface* model_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_CONTROLLER_MATH_CONTROLLER_H_
