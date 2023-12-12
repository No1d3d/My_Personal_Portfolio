#ifndef S21_SMART_CALC_V20_MODELS_MATH_LEXEME_H_
#define S21_SMART_CALC_V20_MODELS_MATH_LEXEME_H_

#include <string>

namespace s21 {

enum LexemeType {
  kUnknownLexeme = 0,   // Неизвестная лексема
  kNumberLexeme = 1,    // число
  kLBracketLexeme = 2,  // (
  kRBracketLexeme = 3,  // )
  kAddLexeme = 4,       // +
  kSubLexeme = 5,       // -
  kDivLexeme = 6,       // /
  kMulLexeme = 7,       // *
  kPowLexeme = 8,       // ^
  kModLexeme = 9,       // mod или % (остаток от деления)
  kUnPlusLexeme = 10,   // Унарный плюс
  kUnMinusLexeme = 11,  // Унарный минус
  kCosLexeme = 12,      // cos
  kSinLexeme = 13,      // sin
  kTanLexeme = 14,      // tan
  kAcosLexeme = 15,     // acos
  kAsinLexeme = 16,     // asin
  kAtanLexeme = 17,     // atan
  kSqrtLexeme = 18,     // sqrt
  kLnLexeme = 19,       // ln
  kLogLexeme = 20,      // log
  kXLexeme = 21,        // x
  kPiLexeme = 22,       // Математическая константа Пи
  kELexeme = 23,        // Математическая константа Е
};

struct Lexeme final {
 public:
  Lexeme();
  Lexeme(LexemeType type, const std::string &str, int priority,
         bool left2right);
  Lexeme(LexemeType type, const std::string &str, int priority, bool left2right,
         double value);

  static Lexeme MakeLexeme(LexemeType type, double value = 0,
                           const std::string &string = "");

  bool IsConstant() const noexcept;
  bool IsFunction() const noexcept;
  bool IsOperator() const noexcept;
  bool IsUnary() const noexcept;
  bool IsBinary() const noexcept;

  LexemeType type;
  std::string str;
  int priority;
  bool left2right;
  double value;

 private:
  static constexpr double kMathPi = 3.14159265358979323846264338327950288;
  static constexpr double kMathE = 2.71828182845904523536028747135266250;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_MATH_LEXEME_H_