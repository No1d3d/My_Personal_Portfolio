#include <gtest/gtest.h>

#include <string>

#include "../models/math/math_model.h"

namespace {

void TestAddLexemeToStringOk(const std::string &src, const s21::Lexeme &add,
                             const std::string &check) {
  s21::MathCalcModel model{src};
  model.MathExpressionAddString(add.str);
  std::string result2 = model.get_math_expression();
  EXPECT_EQ(result2, check);
}

void TestModelAddLexemeToStringFail(const std::string &src,
                                    const s21::Lexeme &add) {
  s21::MathCalcModel model{src};
  model.MathExpressionAddString(add.str);
}

void TestAddPointToString(const std::string &src, const std::string &check) {
  s21::MathCalcModel model{src};
  model.MathExpressionAddString(".");
  std::string result2 = model.get_math_expression();
  EXPECT_EQ(result2, check);
}

void TestModelAddPointToStringFail(const std::string &src) {
  s21::MathCalcModel model{src};
  model.MathExpressionAddString(".");
}

void TestBacspaceStringOk(const std::string &src, const std::string &check) {
  s21::MathCalcModel model{src};
  model.MathExpressionEraseEnd();
  std::string result2 = model.get_math_expression();
  EXPECT_EQ(result2, check);
}

TEST(TestButtons, TestAddLexemeToStringFail1) {
  std::string src = "";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kSubLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kMulLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kDivLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kModLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kPowLexeme)),
               s21::S21WrongOperatorException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail2) {
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "5 + c + 5", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "5 + c", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "5 + co", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "5 + .", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "5 + g", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "c", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "co", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   ".", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   "g", s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputIncorrectException);
}

TEST(TestButtons, TestAddLexemeToStringFail3) {
  std::string src = "5";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail4) {
  std::string src = "5 +";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  EXPECT_THROW(TestModelAddLexemeToStringFail(src, add),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail5) {
  std::string src = "5 + cos (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  EXPECT_THROW(TestModelAddLexemeToStringFail(src, add),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail6) {
  std::string src = "5 + cos ( sin (x) + tan (x) )";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  EXPECT_THROW(TestModelAddLexemeToStringFail(src, add),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail7) {
  std::string src = "5 + cos (x) + sin(x)";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  EXPECT_THROW(TestModelAddLexemeToStringFail(src, add),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail8) {
  std::string src = "log (";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kSubLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kMulLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kDivLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kModLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kPowLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail9) {
  std::string src = "log ( -";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kSubLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kMulLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kDivLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kModLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kPowLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21WrongOperatorException);

  std::string src2 = "log ( +";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kSubLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kMulLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kDivLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kModLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kPowLexeme)),
               s21::S21WrongOperatorException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src2, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21WrongOperatorException);
}

TEST(TestButtons, TestAddLexemeToStringFail10) {
  std::string src =
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2222";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAddLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kSubLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kMulLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kDivLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kModLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kPowLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kRBracketLexeme)),
               s21::S21InputTooLongException);
}

TEST(TestButtons, TestAddLexemeToStringFail11) {
  std::string src =
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 +";

  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kCosLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kSinLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kTanLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAcosLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kAsinLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kLnLexeme)),
               s21::S21InputTooLongException);
  EXPECT_THROW(TestModelAddLexemeToStringFail(
                   src, s21::Lexeme::MakeLexeme(s21::kLogLexeme)),
               s21::S21InputTooLongException);
}

TEST(TestButtons, TestAddPointToStringFail1) {
  std::string src = "3.8.7";

  EXPECT_THROW(TestModelAddPointToStringFail(src),
               s21::S21InputIncorrectException);
}

TEST(TestButtons, TestAddPointToStringFail2) {
  EXPECT_THROW(TestModelAddPointToStringFail("5 + c + 5"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("5 + c"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("5 + co"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("5 + ."),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("5 + g"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("c"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("co"),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("."),
               s21::S21InputIncorrectException);
  EXPECT_THROW(TestModelAddPointToStringFail("g"),
               s21::S21InputIncorrectException);
}

TEST(TestButtons, TestAddPointToStringFail3) {
  std::string src =
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2222";

  EXPECT_THROW(TestModelAddPointToStringFail(src),
               s21::S21InputTooLongException);
}

TEST(TestButtons, TestAddPointToStringFail4) {
  std::string src =
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 222";

  EXPECT_THROW(TestModelAddPointToStringFail(src),
               s21::S21InputTooLongException);
}

TEST(TestButtons, TestAddLexemeOk1) {
  std::string src = "";
  std::string check = "3";

  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 3, "3");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk2) {
  std::string src = "3";
  std::string check = "32";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 2, "2");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk3) {
  std::string src = "32.5";
  std::string check = "32.59";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 9, "9");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk4) {
  std::string src = "000";
  std::string check = "0005";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 5, "5");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk5) {
  std::string src = "5.";
  std::string check = "5.1";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 1, "1");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk6) {
  std::string src = "5";
  std::string check = "5 +";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kAddLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk7) {
  std::string src = "5";
  std::string check = "5 mod";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kModLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk8) {
  std::string src = "5 +";
  std::string check = "5 + cos (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kCosLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk9) {
  std::string src = "5 + cos (";
  std::string check = "5 + cos ( log (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kLogLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk10) {
  std::string src = "5 + cos (";
  std::string check = "5 + cos ( log (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kLogLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk11) {
  std::string src = "";
  std::string check = "9";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 9, "9");

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "98";
  add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 8, "8");

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "98 /";
  add = s21::Lexeme::MakeLexeme(s21::kDivLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "98 / asin (";
  add = s21::Lexeme::MakeLexeme(s21::kAsinLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "98 / asin ( 7";
  add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 7, "7");

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "98 / asin ( 7 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme, 7, "7");

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk12) {
  std::string src = "5";
  std::string check = "5 +";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kAddLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 -";
  add = s21::Lexeme::MakeLexeme(s21::kSubLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 /";
  add = s21::Lexeme::MakeLexeme(s21::kDivLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 *";
  add = s21::Lexeme::MakeLexeme(s21::kMulLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 mod";
  add = s21::Lexeme::MakeLexeme(s21::kModLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 +";
  add = s21::Lexeme::MakeLexeme(s21::kAddLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + cos ( 3 +";
  check = "5 + cos ( 3 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + cos ( 3 -";
  check = "5 + cos ( 3 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + cos ( 3 *";
  check = "5 + cos ( 3 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + cos ( 3 /";
  check = "5 + cos ( 3 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + cos ( 3 mod";
  check = "5 + cos ( 3 )";
  add = s21::Lexeme::MakeLexeme(s21::kRBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk13) {
  std::string src = "5";
  std::string check = "5 * sqrt (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kSqrtLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5.33";
  check = "5.33 * atan (";
  add = s21::Lexeme::MakeLexeme(s21::kAtanLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "x";
  check = "x * asin (";
  add = s21::Lexeme::MakeLexeme(s21::kAsinLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "pi";
  check = "pi * acos (";
  add = s21::Lexeme::MakeLexeme(s21::kAcosLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "e";
  check = "e * ln (";
  add = s21::Lexeme::MakeLexeme(s21::kLnLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + (3 -2)";
  check = "5 + ( 3 - 2 ) * log (";
  add = s21::Lexeme::MakeLexeme(s21::kLogLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk14) {
  std::string src = "5 + (3 -2)";
  std::string check = "5 + ( 3 - 2 ) * e";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kELexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 + ( 3 - 2 ) * e * e";
  add = s21::Lexeme::MakeLexeme(s21::kELexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = check;
  check = "5 + ( 3 - 2 ) * e * e * pi";
  add = s21::Lexeme::MakeLexeme(s21::kPiLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk15) {
  std::string src = "5";
  std::string check = "5 * (";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "pi";
  check = "pi * (";
  add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "e     ";
  check = "e * (";
  add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "    x     ";
  check = "x * (";
  add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * (";
  add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "5 + ( 3 - 2 ) * e * e * pi";
  check = "5 + ( 3 - 2 ) * e * e * pi * (";
  add = s21::Lexeme::MakeLexeme(s21::kLBracketLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk16) {
  std::string src = "";
  std::string check = "pi";
  s21::Lexeme add = s21::Lexeme::MakeLexeme(s21::kPiLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "pi";
  check = "pi * 9";
  add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 9, "9");

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * 9";
  add = s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 9, "9");

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * pi";
  add = s21::Lexeme::MakeLexeme(s21::kPiLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * e";
  add = s21::Lexeme::MakeLexeme(s21::kELexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * x";
  add = s21::Lexeme::MakeLexeme(s21::kXLexeme);

  TestAddLexemeToStringOk(src, add, check);

  src = "(pi + e)";
  check = "( pi + e ) * tan (";
  add = s21::Lexeme::MakeLexeme(s21::kTanLexeme);

  TestAddLexemeToStringOk(src, add, check);
}

TEST(TestButtons, TestAddLexemeOk17) {
  TestAddLexemeToStringOk("", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "-");
  TestAddLexemeToStringOk("-", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "");
  TestAddLexemeToStringOk("--", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "-");
  TestAddLexemeToStringOk("---", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "");
  TestAddLexemeToStringOk("---+", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "");
  TestAddLexemeToStringOk("---+++++",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "");
  TestAddLexemeToStringOk("----+++++",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "-");
  TestAddLexemeToStringOk("---++-",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "-");
  TestAddLexemeToStringOk("+---++-",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "-");
  TestAddLexemeToStringOk("+---++-+",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "-");
  TestAddLexemeToStringOk("+----+",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "-");
}

TEST(TestButtons, TestAddLexemeOk18) {
  TestAddLexemeToStringOk("7", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "- 7");
  TestAddLexemeToStringOk("-7", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "7");
  TestAddLexemeToStringOk("--7", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "- 7");
  TestAddLexemeToStringOk("---7", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "7");
  TestAddLexemeToStringOk("---+7", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "7");
  TestAddLexemeToStringOk("---+++++7",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "7");
  TestAddLexemeToStringOk("----+++++7",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "- 7");
  TestAddLexemeToStringOk("---++-7",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "- 7");
  TestAddLexemeToStringOk(
      "+---++-7.2", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "- 7.2");
  TestAddLexemeToStringOk(
      "+---++-+7.2", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "- 7.2");
  TestAddLexemeToStringOk(
      "+----+7.2", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "- 7.2");
}

TEST(TestButtons, TestAddLexemeOk19) {
  TestAddLexemeToStringOk(
      "log(6)", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme), "log ( 6 ) * -");
  TestAddLexemeToStringOk("log(6", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "log ( - 6");
  TestAddLexemeToStringOk("log6", s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "log - 6");
  TestAddLexemeToStringOk("(pi + e)",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "( pi + e ) * -");
  TestAddLexemeToStringOk("( pi + e ) * -",
                          s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "( pi + e ) *");
}

TEST(TestButtons, TestAddLexemeOk20) {
  std::string src = "";

  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLBracketLexeme),
                          "(");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "-");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kCosLexeme),
                          "cos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSinLexeme),
                          "sin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kTanLexeme),
                          "tan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAcosLexeme),
                          "acos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAsinLexeme),
                          "asin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAtanLexeme),
                          "atan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSqrtLexeme),
                          "sqrt (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLnLexeme), "ln (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLogLexeme),
                          "log (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kELexeme), "e");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kPiLexeme), "pi");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kXLexeme), "x");
}

TEST(TestButtons, TestAddLexemeOk21) {
  std::string src = "5";
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAddLexeme), "5 +");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSubLexeme), "5 -");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kMulLexeme), "5 *");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kDivLexeme), "5 /");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kModLexeme),
                          "5 mod");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kPowLexeme), "5 ^");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLBracketLexeme),
                          "5 * (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "- 5");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kCosLexeme),
                          "5 * cos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSinLexeme),
                          "5 * sin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kTanLexeme),
                          "5 * tan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAcosLexeme),
                          "5 * acos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAsinLexeme),
                          "5 * asin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAtanLexeme),
                          "5 * atan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSqrtLexeme),
                          "5 * sqrt (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLnLexeme),
                          "5 * ln (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLogLexeme),
                          "5 * log (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kELexeme), "5 * e");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kPiLexeme),
                          "5 * pi");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kXLexeme), "5 * x");
}

TEST(TestButtons, TestAddLexemeOk22) {
  std::string src = "5+";
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAddLexeme), "5 +");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSubLexeme), "5 -");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kMulLexeme), "5 *");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kDivLexeme), "5 /");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kModLexeme),
                          "5 mod");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kPowLexeme), "5 ^");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLBracketLexeme),
                          "5 + (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kUnMinusLexeme),
                          "5 + -");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kCosLexeme),
                          "5 + cos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSinLexeme),
                          "5 + sin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kTanLexeme),
                          "5 + tan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAcosLexeme),
                          "5 + acos (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAsinLexeme),
                          "5 + asin (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kAtanLexeme),
                          "5 + atan (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kSqrtLexeme),
                          "5 + sqrt (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLnLexeme),
                          "5 + ln (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kLogLexeme),
                          "5 + log (");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kELexeme), "5 + e");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kPiLexeme),
                          "5 + pi");
  TestAddLexemeToStringOk(src, s21::Lexeme::MakeLexeme(s21::kXLexeme), "5 + x");
}

TEST(TestButtons, TestAddPointOk1) {
  std::string src = "3";
  std::string check = "3.";

  TestAddPointToString(src, check);
}

TEST(TestButtons, TestAddPointOk2) {
  TestAddPointToString("3", "3.");
  TestAddLexemeToStringOk(
      "3.", s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 2, "2"), "3.2");
  TestAddLexemeToStringOk(
      "3.2", s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 3, "3"), "3.23");
}

TEST(TestButtons, TestAddPointOk3) {
  std::string src = "3.";
  std::string check = "3.";

  TestAddPointToString(src, check);
  TestAddPointToString(src, check);
  TestAddPointToString(src, check);
}

TEST(TestButtons, TestAddPointOk4) {
  std::string src = "";
  std::string check = "0.";

  TestAddPointToString(src, check);
}

TEST(TestButtons, TestAddPointOk5) {
  std::string src = "3.87";
  std::string check = "3.87";

  TestAddPointToString(src, check);
}

TEST(TestButtons, TestAddPointOk6) {
  TestAddPointToString("5 +", "5 + 0.");
  TestAddPointToString("5 mod", "5 mod 0.");
  TestAddPointToString("5 ^", "5 ^ 0.");
  TestAddPointToString("5 + (", "5 + ( 0.");
  TestAddPointToString("5 + cos (", "5 + cos ( 0.");
  TestAddPointToString("e", "e * 0.");
  TestAddPointToString("pi", "pi * 0.");
  TestAddPointToString("x", "x * 0.");
  TestAddPointToString("5 + cos", "5 + cos 0.");
  TestAddPointToString("( 5 + 2 )", "( 5 + 2 ) * 0.");
}

TEST(TestButtons, TestAddPointOk7) {
  TestAddPointToString("-", "- 0.");
  TestAddPointToString("+", "+ 0.");
  TestAddPointToString("cos-", "cos - 0.");
  TestAddPointToString("5 + ( -", "5 + ( - 0.");
}

TEST(TestButtons, TestAddPointOk8) {
  TestAddPointToString("3.876 + 2", "3.876 + 2.");
  TestAddLexemeToStringOk("3.876 + 2.",
                          s21::Lexeme::MakeLexeme(s21::kNumberLexeme, 9, "9"),
                          "3.876 + 2.9");
}

TEST(TestButtons, TestBackspaceOk1) {
  std::string src = "3.77";
  std::string check = "3.7";

  TestBacspaceStringOk(src, check);
}

TEST(TestButtons, TestBackspaceOk2) {
  std::string src = "321.65";

  TestBacspaceStringOk(src, "321.6");
  TestBacspaceStringOk("321.6", "321.");
  TestBacspaceStringOk("321.", "321");
  TestBacspaceStringOk("321", "32");
  TestBacspaceStringOk("32", "3");
  TestBacspaceStringOk("3", "");
  TestBacspaceStringOk("", "");
  TestBacspaceStringOk("", "");
  TestBacspaceStringOk("", "");
  TestBacspaceStringOk("", "");
}

TEST(TestButtons, TestBackspaceOk3) {
  TestBacspaceStringOk("-(cos(x^4) * asin(x)/20)^1.33",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1.3");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1.3",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1.");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1.",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^ 1",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20 ) ^",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20 )");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20 )",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 20");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 20",
                       "- ( cos ( x ^ 4 ) * asin ( x ) / 2");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) / 2",
                       "- ( cos ( x ^ 4 ) * asin ( x ) /");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x ) /",
                       "- ( cos ( x ^ 4 ) * asin ( x )");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x )",
                       "- ( cos ( x ^ 4 ) * asin ( x");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin ( x",
                       "- ( cos ( x ^ 4 ) * asin (");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) * asin (", "- ( cos ( x ^ 4 ) *");
  TestBacspaceStringOk("- ( cos ( x ^ 4 ) *", "- ( cos ( x ^ 4 )");
  TestBacspaceStringOk("- ( cos ( x ^ 4 )", "- ( cos ( x ^ 4");
  TestBacspaceStringOk("- ( cos ( x ^ 4", "- ( cos ( x ^");
  TestBacspaceStringOk("- ( cos ( x ^", "- ( cos ( x");
  TestBacspaceStringOk("- ( cos ( x", "- ( cos (");
  TestBacspaceStringOk("- ( cos (", "- (");
  TestBacspaceStringOk("- (", "-");
  TestBacspaceStringOk("-", "");
  TestBacspaceStringOk("", "");
  TestBacspaceStringOk("", "");
  TestBacspaceStringOk("", "");
}

TEST(TestButtons, TestBackspaceFail1) {
  TestBacspaceStringOk("5 + co", "5 + c");
  TestBacspaceStringOk("5 + c", "5 + ");
  TestBacspaceStringOk("5 + ", "5");
  TestBacspaceStringOk("5", "");
  TestBacspaceStringOk("", "");

  TestBacspaceStringOk("3.8.7", "3.8.");
  TestBacspaceStringOk("3.8.", "3.8");
  TestBacspaceStringOk("3.8", "3.");
  TestBacspaceStringOk("3.", "3");
  TestBacspaceStringOk("3", "");
  TestBacspaceStringOk("", "");

  TestBacspaceStringOk("5 + g", "5 + ");
  TestBacspaceStringOk("5 + ", "5");
  TestBacspaceStringOk("5", "");
  TestBacspaceStringOk("", "");
}

}  // namespace