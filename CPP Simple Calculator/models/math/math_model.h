#ifndef S21_SMART_CALC_V20_MODELS_MATH_MATH_MODEL_H_
#define S21_SMART_CALC_V20_MODELS_MATH_MATH_MODEL_H_

#include <list>
#include <string>

#include "../calc_exception.h"
#include "lexeme.h"

namespace s21 {

class MathCalcModel final {
 public:
  static constexpr std::size_t kMaxInputSize = 255;

  MathCalcModel();
  explicit MathCalcModel(const std::string& string);
  MathCalcModel(const MathCalcModel& other) = delete;
  MathCalcModel(MathCalcModel&& other) = delete;
  MathCalcModel& operator=(const MathCalcModel& other) = delete;
  MathCalcModel& operator=(MathCalcModel&& other) = delete;
  ~MathCalcModel() = default;

  void set_math_expression(const std::string& new_expression);
  void set_x_value(double new_value) { x_value_ = new_value; }
  void MathExpressionAddString(const std::string& add);
  void MathExpressionEraseEnd();

  std::string get_math_expression() const { return math_expression_; }
  std::string get_rpn_expression();
  double get_x_value() const noexcept { return x_value_; }
  double get_result() const noexcept { return result_; }
  bool get_is_calculated() const noexcept { return is_calculated_; }

  void Calculate();

 private:
  void InitMathCalcModel();
  void CalculateRpn();
  void InitCalcMachine();
  void ResetModelResults() noexcept;
  double CalculateX(double x = 0);
  double CalculateUnaryOp(double value, LexemeType type) const noexcept;
  double CalculateBinaryOp(double num1, double num2,
                           LexemeType type) const noexcept;

  bool need_to_init_model_;
  bool is_calculated_;
  double x_value_;
  std::string math_expression_;
  std::string rpn_expression_;
  std::list<Lexeme> calc_lexemes_list_;
  double result_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_MATH_MATH_MODEL_H_