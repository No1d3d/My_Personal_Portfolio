#include "math_model.h"

#include <cmath>   // for std::sin & etc
#include <limits>  // for std::numeric_limits
#include <list>    // for std::list
#include <stack>   // for std::stack

#include "lexer.h"

namespace s21 {

MathCalcModel::MathCalcModel() : MathCalcModel("") {}

MathCalcModel::MathCalcModel(const std::string& string)
    : need_to_init_model_(true),
      is_calculated_(false),
      x_value_(0.0),
      math_expression_(string),
      rpn_expression_(""),
      calc_lexemes_list_({}),
      result_(std::numeric_limits<double>::quiet_NaN()) {}

void MathCalcModel::set_math_expression(const std::string& new_expression) {
  if (math_expression_ != new_expression) {
    math_expression_ = new_expression;
    need_to_init_model_ = true;
    is_calculated_ = false;
  }
}

void MathCalcModel::MathExpressionAddString(const std::string& add) {
  std::string result = get_math_expression();

  if (result.length() > kMaxInputSize) {
    throw S21InputTooLongException("Input string too long");
  }

  try {
    if (add == ".") {
      result = Lexer::AddPointToString(result);
    } else {
      auto lexemes_list = Lexer::ParseLexemes(add);
      for (auto& item : lexemes_list) {
        result = Lexer::AddLexemeToString(result, item);
      }
    }
  } catch (std::invalid_argument&) {
    throw S21InputIncorrectException("Input incorrect");
  } catch (std::logic_error&) {
    throw S21WrongOperatorException("Wrong operator");
  }

  if (result.length() > kMaxInputSize) {
    throw S21InputTooLongException("Input string too long");
  }

  set_math_expression(result);
}

void MathCalcModel::MathExpressionEraseEnd() {
  std::string result = get_math_expression();
  try {
    result = Lexer::RemoveLexemeFromStringEnd(result);
  } catch (std::invalid_argument&) {
    if (result.length() > 0) {
      result.erase(--result.end());
    }
  }
  set_math_expression(result);
}

std::string MathCalcModel::get_rpn_expression() {
  if (need_to_init_model_ == true) {
    InitMathCalcModel();
  }

  return rpn_expression_;
}

void MathCalcModel::Calculate() {
  ResetModelResults();
  result_ = CalculateX(x_value_);
}

void MathCalcModel::InitMathCalcModel() {
  CalculateRpn();
  InitCalcMachine();
  need_to_init_model_ = false;
}

void MathCalcModel::CalculateRpn() {
  if (math_expression_.length() == 0) {
    throw S21InputZeroLengthException("The input string must be longer than 0");
  }

  if (math_expression_.length() > kMaxInputSize) {
    throw S21InputTooLongException("The input string is too long");
  }

  std::list<Lexeme> lexemes_list;

  try {
    lexemes_list = Lexer::ParseLexemes(math_expression_);
  } catch (std::invalid_argument&) {
    throw S21InputIncorrectException("Invalid characters in input string");
  }

  if (lexemes_list.size() == 0) {
    throw S21InputIncorrectException(
        "The input string must contain valid tokens");
  }

  std::stack<Lexeme> lexemes_stack;
  std::string result;

  Lexer::FixLexemesList(lexemes_list);

  auto lexemes_begin = lexemes_list.begin();
  auto lexemes_end = lexemes_list.end();

  for (; lexemes_begin != lexemes_end; ++lexemes_begin) {
    Lexeme check = *lexemes_begin;

    if (check.type == kUnPlusLexeme) {
      continue;
    } else if (check.IsConstant()) {
      result.append(check.str);
      result.append(" ");
    } else if (check.type == kLBracketLexeme || check.IsFunction()) {
      lexemes_stack.push(check);
    } else if (check.type == kRBracketLexeme) {
      while (1) {
        if (lexemes_stack.size() == 0) {
          throw S21InputIncorrectException("Brackets are not matched");
        }

        Lexeme top = lexemes_stack.top();
        if (top.type == kLBracketLexeme) {
          lexemes_stack.pop();
          break;
        } else {
          result.append(top.str);
          result.append(" ");
          lexemes_stack.pop();
        }
      }

      if (lexemes_stack.size() != 0) {
        Lexeme top = lexemes_stack.top();
        if (top.IsFunction()) {
          result.append(top.str);
          result.append(" ");
          lexemes_stack.pop();
        }
      }
    } else if (check.IsOperator()) {
      while (1) {
        if (lexemes_stack.size() == 0) {
          break;
        }

        Lexeme top = lexemes_stack.top();
        if ((top.left2right == true && top.priority >= check.priority) ||
            (top.left2right == false && top.priority > check.priority)) {
          result.append(top.str);
          result.append(" ");
          lexemes_stack.pop();
        } else {
          break;
        }
      }
      lexemes_stack.push(check);
    } else {
      throw S21InputIncorrectException("Unknown token");
    }
  }

  while (lexemes_stack.size() > 0) {
    Lexeme top = lexemes_stack.top();
    if (top.type == kLBracketLexeme || top.type == kRBracketLexeme) {
      throw S21InputIncorrectException("Brackets are not matched");
    }

    result.append(top.str);
    result.append(" ");
    lexemes_stack.pop();
  }

  if (result.length() > 0 && *(--result.end()) == ' ') {
    result.erase(--result.end());
  }

  rpn_expression_ = result;
}

void MathCalcModel::InitCalcMachine() {
  try {
    calc_lexemes_list_ = Lexer::ParseLexemes(rpn_expression_);
  } catch (std::invalid_argument&) {
    throw S21InputIncorrectException("Invalid characters in input string");
  }
}

void MathCalcModel::ResetModelResults() noexcept {
  result_ = std::numeric_limits<double>::quiet_NaN();
}

double MathCalcModel::CalculateX(double x) {
  if (need_to_init_model_ == true) {
    InitMathCalcModel();
  }

  double result = 0.0;
  std::stack<Lexeme> lexemes_stack;

  auto lexemes_begin = calc_lexemes_list_.begin();
  auto lexemes_end = calc_lexemes_list_.end();

  for (; lexemes_begin != lexemes_end; ++lexemes_begin) {
    Lexeme check = *lexemes_begin;
    if (check.type == kNumberLexeme) {
      lexemes_stack.push(check);
    } else if (check.type == kXLexeme) {
      lexemes_stack.push(Lexeme::MakeLexeme(kNumberLexeme, x));
    } else if (check.IsConstant()) {
      lexemes_stack.push(Lexeme::MakeLexeme(kNumberLexeme, check.value));
    } else if (check.IsUnary()) {
      if (lexemes_stack.size() > 0) {
        Lexeme top = lexemes_stack.top();
        lexemes_stack.pop();
        double res = CalculateUnaryOp(top.value, check.type);
        lexemes_stack.push(Lexeme::MakeLexeme(kNumberLexeme, res));
      } else {
        throw S21InputIncorrectException("Calculate error");
      }
    } else if (check.IsBinary()) {
      if (lexemes_stack.size() > 0) {
        Lexeme lexeme1 = lexemes_stack.top();
        lexemes_stack.pop();
        if (lexemes_stack.size() > 0) {
          Lexeme lexeme2 = lexemes_stack.top();
          lexemes_stack.pop();
          double res =
              CalculateBinaryOp(lexeme2.value, lexeme1.value, check.type);
          lexemes_stack.push(Lexeme::MakeLexeme(kNumberLexeme, res));
        } else {
          throw S21InputIncorrectException("Calculate error");
        }
      } else {
        throw S21InputIncorrectException("Calculate error");
      }
    } else {
      throw S21InputIncorrectException("Unknown token");
    }
  }
  if (lexemes_stack.size() == 0) {
    throw S21InputIncorrectException("Calculate error");
  }

  Lexeme last = lexemes_stack.top();
  lexemes_stack.pop();
  if (lexemes_stack.size() > 0) {
    throw S21InputIncorrectException("Calculate error");
  } else {
    result = last.value;
  }

  is_calculated_ = true;
  return result;
}

double MathCalcModel::CalculateUnaryOp(double value,
                                       LexemeType type) const noexcept {
  double result = 0.0;

  switch (type) {
    case kUnMinusLexeme:
      result = 0 - value;
      break;
    case kCosLexeme:
      result = std::cos(value);
      break;
    case kSinLexeme:
      result = std::sin(value);
      break;
    case kTanLexeme:
      result = std::tan(value);
      break;
    case kAcosLexeme:
      result = std::acos(value);
      break;
    case kAsinLexeme:
      result = std::asin(value);
      break;
    case kAtanLexeme:
      result = std::atan(value);
      break;
    case kSqrtLexeme:
      result = std::sqrt(value);
      break;
    case kLnLexeme:
      result = std::log(value);
      break;
    case kLogLexeme:
      result = std::log10(value);
      break;
    default:
      break;
  }

  return result;
}

double MathCalcModel::CalculateBinaryOp(double num1, double num2,
                                        LexemeType type) const noexcept {
  double result = 0.0;

  switch (type) {
    case kAddLexeme:
      result = num1 + num2;
      break;
    case kSubLexeme:
      result = num1 - num2;
      break;
    case kDivLexeme:
      result = num1 / num2;
      break;
    case kMulLexeme:
      result = num1 * num2;
      break;
    case kPowLexeme:
      result = std::pow(num1, num2);
      break;
    case kModLexeme:
      result = std::fmod(num1, num2);
      break;
    default:
      break;
  }

  return result;
}

}  // namespace s21
