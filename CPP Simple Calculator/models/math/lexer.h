#ifndef S21_SMART_CALC_V20_MODELS_MATH_LEXER_H_
#define S21_SMART_CALC_V20_MODELS_MATH_LEXER_H_

#include <list>         // for std::list
#include <map>          // for std::map
#include <string>       // for std::string
#include <string_view>  // for std::string_view

#include "lexeme.h"

namespace s21 {

class Lexer final {
 public:
  Lexer() = delete;
  ~Lexer() = delete;

  static std::list<Lexeme> ParseLexemes(const std::string&);
  static void FixLexemesList(std::list<Lexeme>&);
  static void FixUnPlusMinusLexemesList(std::list<Lexeme>&);
  static std::string AddLexemeToString(const std::string&, const Lexeme&);
  static std::string AddPointToString(const std::string&);
  static std::string RemoveLexemeFromStringEnd(const std::string&);
  static std::string LexemeListToString(const std::list<Lexeme>&);

 private:
  struct CmpByStringLength {
    bool operator()(const std::string& a, const std::string& b) const {
      if (a.length() == b.length()) {
        return a < b;
      }
      return a.length() > b.length();
    }
  };

  static std::pair<Lexeme, std::string_view> GetNonNumberLexemeFromString(
      const std::string_view&);
  static std::pair<Lexeme, std::string_view> GetNumberLexemeFromString(
      const std::string_view&);
  static bool IsLbracketExist(const std::list<Lexeme>&);
  static void AddUnMinusToList(std::list<Lexeme>& lexemes_list);
  inline static const std::map<std::string, LexemeType, CmpByStringLength>
      types_map_{
          {"(", kLBracketLexeme}, {")", kRBracketLexeme}, {"+", kAddLexeme},
          {"-", kSubLexeme},      {"/", kDivLexeme},      {"*", kMulLexeme},
          {"^", kPowLexeme},      {"~", kUnMinusLexeme},  {"%", kModLexeme},
          {"x", kXLexeme},        {"e", kELexeme},        {"mod", kModLexeme},
          {"cos", kCosLexeme},    {"sin", kSinLexeme},    {"tan", kTanLexeme},
          {"acos", kAcosLexeme},  {"asin", kAsinLexeme},  {"atan", kAtanLexeme},
          {"sqrt", kSqrtLexeme},  {"ln", kLnLexeme},      {"log", kLogLexeme},
          {"pi", kPiLexeme}};
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_MATH_LEXER_H_