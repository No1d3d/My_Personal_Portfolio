#include "lexeme.h"

#include <limits>

namespace s21 {
Lexeme::Lexeme()
    : type(kUnknownLexeme), str(""), priority(0), left2right(true), value(0) {}

Lexeme::Lexeme(LexemeType type, const std::string &str, int priority,
               bool left2right, double value)
    : type(type),
      str(str),
      priority(priority),
      left2right(left2right),
      value(value) {}
Lexeme::Lexeme(LexemeType type, const std::string &str, int priority,
               bool left2right)
    : type(type),
      str(str),
      priority(priority),
      left2right(left2right),
      value(std::numeric_limits<double>::quiet_NaN()) {}

Lexeme Lexeme::MakeLexeme(LexemeType type, double value,
                          const std::string &string) {
  switch (type) {
    case kLBracketLexeme:
      return Lexeme{kLBracketLexeme, "(", 0, true};
    case kRBracketLexeme:
      return Lexeme{kRBracketLexeme, ")", 0, true};
    case kAddLexeme:
      return Lexeme{kAddLexeme, "+", 1, true};
    case kSubLexeme:
      return Lexeme{kSubLexeme, "-", 1, true};
    case kDivLexeme:
      return Lexeme{kDivLexeme, "/", 2, true};
    case kMulLexeme:
      return Lexeme{kMulLexeme, "*", 2, true};
    case kPowLexeme:
      return Lexeme{kPowLexeme, "^", 3, false};
    case kUnMinusLexeme:
      return Lexeme{kUnMinusLexeme, "~", 3, false};
    case kUnPlusLexeme:
      return Lexeme{kUnPlusLexeme, "+", 3, false};
    case kNumberLexeme:
      return Lexeme{kNumberLexeme, string, 0, true, value};
    case kModLexeme:
      return Lexeme{kModLexeme, "mod", 2, true};
    case kCosLexeme:
      return Lexeme{kCosLexeme, "cos", 0, true};
    case kSinLexeme:
      return Lexeme{kSinLexeme, "sin", 0, true};
    case kTanLexeme:
      return Lexeme{kTanLexeme, "tan", 0, true};
    case kAcosLexeme:
      return Lexeme{kAcosLexeme, "acos", 0, true};
    case kAsinLexeme:
      return Lexeme{kAsinLexeme, "asin", 0, true};
    case kAtanLexeme:
      return Lexeme{kAtanLexeme, "atan", 0, true};
    case kSqrtLexeme:
      return Lexeme{kSqrtLexeme, "sqrt", 0, true};
    case kLnLexeme:
      return Lexeme{kLnLexeme, "ln", 0, true};
    case kLogLexeme:
      return Lexeme{kLogLexeme, "log", 0, true};
    case kXLexeme:
      return Lexeme{kXLexeme, "x", 0, true};
    case kPiLexeme:
      return Lexeme{kPiLexeme, "pi", 0, true, Lexeme::kMathPi};
    case kELexeme:
      return Lexeme{kELexeme, "e", 0, true, Lexeme::kMathE};
    case kUnknownLexeme:
    default:
      return Lexeme{kUnknownLexeme, "", 0, false};
  }
}

bool Lexeme::IsConstant() const noexcept {
  if (type == kNumberLexeme || type == kXLexeme || type == kELexeme ||
      type == kPiLexeme) {
    return true;
  }

  return false;
}

bool Lexeme::IsFunction() const noexcept {
  if (type == kCosLexeme || type == kSinLexeme || type == kTanLexeme ||
      type == kAcosLexeme || type == kAsinLexeme || type == kAtanLexeme ||
      type == kSqrtLexeme || type == kLnLexeme || type == kLogLexeme) {
    return true;
  }

  return false;
}

bool Lexeme::IsOperator() const noexcept {
  if (type == kAddLexeme || type == kSubLexeme || type == kDivLexeme ||
      type == kMulLexeme || type == kPowLexeme || type == kUnMinusLexeme ||
      type == kUnPlusLexeme || type == kModLexeme) {
    return true;
  }

  return false;
}

bool Lexeme::IsUnary() const noexcept {
  if (type == kUnMinusLexeme || type == kUnPlusLexeme || type == kCosLexeme ||
      type == kSinLexeme || type == kTanLexeme || type == kAcosLexeme ||
      type == kAsinLexeme || type == kAtanLexeme || type == kSqrtLexeme ||
      type == kLnLexeme || type == kLogLexeme) {
    return true;
  }

  return false;
}

bool Lexeme::IsBinary() const noexcept {
  if (type == kAddLexeme || type == kSubLexeme || type == kDivLexeme ||
      type == kMulLexeme || type == kPowLexeme || type == kModLexeme) {
    return true;
  }

  return false;
}

}  // namespace s21