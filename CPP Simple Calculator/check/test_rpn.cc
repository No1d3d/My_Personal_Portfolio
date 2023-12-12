#include <gtest/gtest.h>

#include <string>

#include "../models/math/math_model.h"

namespace {

void TestGetRpnOk(std::string src, std::string check) {
  s21::MathCalcModel model{src};
  EXPECT_EQ(model.get_rpn_expression(), check);
}

void TestGetRpnFail(std::string src) {
  s21::MathCalcModel model{src};

  EXPECT_ANY_THROW(model.get_rpn_expression());
}

TEST(TestMathCalcModel, TestGetRpnFail00) {
  std::string src = "";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail000) {
  std::string src = "   ";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail1) {
  std::string src = "5*(5+1";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail2) {
  std::string src = "5*(5+1(";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail3) {
  std::string src = "5*)5+1";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail4) {
  std::string src = "5*)5+1)";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail5) {
  std::string src = "5(*))5+1";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail6) {
  std::string src = "5(*))(5+1";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail7) {
  std::string src = "5.5.5 + 1";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail8) {
  std::string src = "5 + 1 + gg";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpnFail9) {
  std::string src =
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + "
      "2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2222";

  TestGetRpnFail(src);
}

TEST(TestMathCalcModel, TestGetRpn1) {
  std::string src = "3.58 + 4 * 2 / 5^2";
  std::string check = "3.58 4 2 * 5 2 ^ / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn2) {
  std::string src = "3 + 4 * 2 / (1 - 5)^2";
  std::string check = "3 4 2 * 1 5 - 2 ^ / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn3) {
  std::string src =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/"
      "(7-(1+1))*3-(2+(1+1)))";
  std::string check =
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 "
      "1 1 + - / 3 * + 2 1 1 + + - * -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn4) {
  std::string src = "5^2^3";
  std::string check = "5 2 3 ^ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn5) {
  std::string src = "5.45-2*5^2^3+2^2^3 +1";
  std::string check = "5.45 2 5 2 3 ^ ^ * - 2 2 3 ^ ^ + 1 +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn6) {
  std::string src = "1";
  std::string check = "1";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn7) {
  std::string src = "(5)*(5)+(1)";
  std::string check = "5 5 * 1 +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn8) {
  std::string src = "3.58 + 4 * 2 / 5^2";
  std::string check = "3.58 4 2 * 5 2 ^ / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn9) {
  std::string src = "3 + 4 * 2 / (1 - 5)^2";
  std::string check = "3 4 2 * 1 5 - 2 ^ / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn10) {
  std::string src =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  std::string check =
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 1 1 + - / 3 * + 2 1 1 + + - * -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn11) {
  std::string src = "5^2^3";
  std::string check = "5 2 3 ^ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn12) {
  std::string src = "5.45-2*5^2^3+2^2^3 +1";
  std::string check = "5.45 2 5 2 3 ^ ^ * - 2 2 3 ^ ^ + 1 +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn13) {
  std::string src = "1";
  std::string check = "1";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn14) {
  std::string src = "1/5^5";
  std::string check = "1 5 5 ^ /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn15) {
  std::string src = "2 % 3";
  std::string check = "2 3 mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn16) {
  std::string src = "2 % -3";
  std::string check = "2 3 ~ mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn17) {
  std::string src = "5 * 5 / 2 % 3";
  std::string check = "5 5 * 2 / 3 mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn18) {
  std::string src = "(5 * 5 / 2) % (3 * 4 / 2)";
  std::string check = "5 5 * 2 / 3 4 * 2 / mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn19) {
  std::string src = "4 * 4 / 2 % 3 * 4 / 2";
  std::string check = "4 4 * 2 / 3 mod 4 * 2 /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn20) {
  std::string src = "2 mod 3";
  std::string check = "2 3 mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn21) {
  std::string src = "2 mod -3";
  std::string check = "2 3 ~ mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn22) {
  std::string src = "(5 * 5 / 2) mod (3 * 4 / 2)";
  std::string check = "5 5 * 2 / 3 4 * 2 / mod";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn23) {
  std::string src = "4 * 4 / 2 mod 3 * 4 / 2";
  std::string check = "4 4 * 2 / 3 mod 4 * 2 /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn24) {
  std::string src = "5.12345679^25";
  std::string check = "5.12345679 25 ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn25) {
  std::string src = "5.1234567555555555^25";
  std::string check = "5.1234567555555555 25 ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn26) {
  std::string src = "pi^e";
  std::string check = "pi e ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn27) {
  std::string src = "-pi^-e";
  std::string check = "pi e ~ ^ ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn28) {
  std::string src = "(-pi^-e + pi * e / pi) - pi*(-e*(cos(pi))) + sin(pi/2)";
  std::string check =
      "pi e ~ ^ ~ pi e * pi / + pi e ~ pi cos * * - pi 2 / sin +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn29) {
  std::string src = "sin(2+3*1.55)";
  std::string check = "2 3 1.55 * + sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn30) {
  std::string src = "-5--5";
  std::string check = "5 ~ 5 ~ -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn31) {
  std::string src = "-5--5+-4";
  std::string check = "5 ~ 5 ~ - 4 ~ +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn32) {
  std::string src = "-1/5^-5";
  std::string check = "1 ~ 5 5 ~ ^ /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn33) {
  std::string src = "2---5";
  std::string check = "2 5 ~ ~ -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn34) {
  std::string src = "--5+(-5-7-(-7*7))";
  std::string check = "5 ~ ~ 5 ~ 7 - 7 ~ 7 * - +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn35) {
  std::string src = "+5+(+5-7-(+7*7))";
  std::string check = "5 5 7 - 7 7 * - +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn36) {
  std::string src =
      "+15/-(7-(1+1))*-3-(-2+(+1+1))*-15/-(7--(200+1))*+3-(2+(1+1))*(15/"
      "-(7-(1+1))*3-(2+(1+1))+15/-(7-+(1+1))*3*-(2+(1+1)))";
  std::string check =
      "15 7 1 1 + - ~ / 3 ~ * 2 ~ 1 1 + + 15 ~ * 7 200 1 + ~ - ~ / 3 * - 2 1 1 "
      "+ + 15 7 1 1 + - ~ / 3 * 2 1 1 + + - 15 7 1 1 + - ~ / 3 * 2 1 1 + + ~ * "
      "+ * -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn37) {
  std::string src =
      "+15/-(7-(1+1))*-3-(-2+(+1+1))*-15/-(7--(200^-2^-5+1))*+3-(2+(1+1))*(15/"
      "-(7-(1+1))*3-(2+(1+1))^+5+15/-(7-+(1^+2^+1+1))*3*-(2^-1+(1+1)))";
  std::string check =
      "15 7 1 1 + - ~ / 3 ~ * 2 ~ 1 1 + + 15 ~ * 7 200 2 5 ~ ^ ~ ^ 1 + ~ - ~ / "
      "3 * - 2 1 1 + + 15 7 1 1 + - ~ / 3 * 2 1 1 + + 5 ^ - 15 7 1 2 1 ^ ^ 1 + "
      "- ~ / 3 * 2 1 ~ ^ 1 1 + + ~ * + * -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn38) {
  std::string src = "+-+-+++7-+--++-+-+++--7";
  std::string check = "7 ~ ~ 7 ~ ~ ~ ~ ~ ~ -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn39) {
  std::string src = "+-+-+++7-+--++-+-+++---7";
  std::string check = "7 ~ ~ 7 ~ ~ ~ ~ ~ ~ ~ -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn40) {
  std::string src =
      "-(2^2^3-(+-+-+++7-+--++-+-+++---7)/2^1^1^1^1) + "
      "(2^2^3-(+-+-+++7-+--++-+-+++---7)/2^-1^+1^-1^+1)";
  std::string check =
      "2 2 3 ^ ^ 7 ~ ~ 7 ~ ~ ~ ~ ~ ~ ~ - 2 1 1 1 1 ^ ^ ^ ^ / - ~ 2 2 3 ^ ^ 7 ~ "
      "~ 7 ~ ~ ~ ~ ~ ~ ~ - 2 1 1 1 1 ^ ~ ^ ^ ~ ^ / - +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn41) {
  std::string src = "5^-3^-4";
  std::string check = "5 3 4 ~ ^ ~ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn42) {
  std::string src = "(5^-3)^-4";
  std::string check = "5 3 ~ ^ 4 ~ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn43) {
  std::string src = "-1^2";
  std::string check = "1 2 ^ ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn44) {
  std::string src = "(-1)^2";
  std::string check = "1 ~ 2 ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn45) {
  std::string src = "2^-2";
  std::string check = "2 2 ~ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn46) {
  std::string src = "1-(2^-2^-3^-4)^-2^3^-2";
  std::string check = "1 2 2 3 4 ~ ^ ~ ^ ~ ^ 2 3 2 ~ ^ ^ ~ ^ -";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn47) {
  std::string src = "5^-1.5^-2.333";
  std::string check = "5 1.5 2.333 ~ ^ ~ ^";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn48) {
  std::string src = "cos(5)";
  std::string check = "5 cos";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn49) {
  std::string src = "cos(-5)";
  std::string check = "5 ~ cos";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn50) {
  std::string src = "-cos(5)";
  std::string check = "5 cos ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn51) {
  std::string src = "sin(10)";
  std::string check = "10 sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn52) {
  std::string src = "sin(-10)";
  std::string check = "10 ~ sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn53) {
  std::string src = "-sin(10)";
  std::string check = "10 sin ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn54) {
  std::string src = "cos(5)+sin(10)";
  std::string check = "5 cos 10 sin +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn55) {
  std::string src = "5^sin(2)^cos(2) + 6^sin(2)^cos(2)";
  std::string check = "5 2 sin 2 cos ^ ^ 6 2 sin 2 cos ^ ^ +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn56) {
  std::string src = "-5^-sin(2)^-cos(2) + -6^-sin(2)^-cos(-2)";
  std::string check = "5 2 sin 2 cos ~ ^ ~ ^ ~ 6 2 sin 2 ~ cos ~ ^ ~ ^ ~ +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn57) {
  std::string src = "tan(5)";
  std::string check = "5 tan";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn58) {
  std::string src = "acos(0)";
  std::string check = "0 acos";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn59) {
  std::string src = "asin(0)";
  std::string check = "0 asin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn60) {
  std::string src = "asin(0.5)";
  std::string check = "0.5 asin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn61) {
  std::string src = "atan(1)";
  std::string check = "1 atan";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn62) {
  std::string src = "atan(-100)";
  std::string check = "100 ~ atan";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn63) {
  std::string src = "sqrt(11.11)";
  std::string check = "11.11 sqrt";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn64) {
  std::string src = "ln(1000.998)";
  std::string check = "1000.998 ln";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn65) {
  std::string src = "log(1000.998)";
  std::string check = "1000.998 log";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn66) {
  std::string src = "sin(cos(tan(-3.14)))";
  std::string check = "3.14 ~ tan cos sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn67) {
  std::string src = "-sin(-cos(-tan(-3.14)))";
  std::string check = "3.14 ~ tan ~ cos ~ sin ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn68) {
  std::string src =
      "log(5.22)^acos(0.33)^atan(1) + sqrt(10)*asin(0.33)^acos(0)/6^tan(1)";
  std::string check =
      "5.22 log 0.33 acos 1 atan ^ ^ 10 sqrt 0.33 asin 0 acos ^ * 6 1 tan ^ / "
      "+";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn69) {
  std::string src =
      "log(5.22)^-acos(-0.33)^-atan(-1) + "
      "-sqrt(10)*-asin(0.33)^-acos(-0)/-6^-tan(-1)";
  std::string check =
      "5.22 log 0.33 ~ acos 1 ~ atan ~ ^ ~ ^ 10 sqrt ~ 0.33 asin 0 ~ acos ~ ^ "
      "~ * 6 1 ~ tan ~ ^ ~ / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn70) {
  std::string src = "sin(x)";
  std::string check = "x sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn71) {
  std::string src = "(x)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn72) {
  std::string src = "(x)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn73) {
  std::string src = "(x)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn74) {
  std::string src = "(x)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn75) {
  std::string src = "(x)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn76) {
  std::string src = "x^x^x/log(x)";
  std::string check = "x x x ^ ^ x log /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn77) {
  std::string src = "x^x^x/log(x)";
  std::string check = "x x x ^ ^ x log /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn78) {
  std::string src = "--5+(-5-x-(-x*7))";
  std::string check = "5 ~ ~ 5 ~ x - x ~ 7 * - +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn79) {
  std::string src = "siN(x)*Cos(X)";
  std::string check = "x sin x cos *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn80) {
  std::string src = "(X)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn81) {
  std::string src = "(X)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn82) {
  std::string src = "(X)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn83) {
  std::string src = "(X)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn84) {
  std::string src = "(X)";
  std::string check = "x";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn85) {
  std::string src = "-(tAn(2.37^-X)  + Ln (-x / 5 + X)  * (X^-x)^X)";
  std::string check = "2.37 x ~ ^ tan x ~ 5 / x + ln x x ~ ^ x ^ * + ~";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn86) {
  std::string src = "X*SIN(X)";
  std::string check = "x x sin *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn87) {
  std::string src = "sin(SIN(Sin(sIn(1/ln(x^123)))))";
  std::string check = "1 x 123 ^ ln / sin sin sin sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn88) {
  std::string src = "sin(SIN(Sin(sIn(1/ln(x^123)))))";
  std::string check = "1 x 123 ^ ln / sin sin sin sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn89) {
  std::string src = "sin(SIN(Sin(sIn(1/ln(x^123)))))";
  std::string check = "1 x 123 ^ ln / sin sin sin sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn90) {
  std::string src = "sin(SIN(Sin(sIn(1/ln(x^123)))))";
  std::string check = "1 x 123 ^ ln / sin sin sin sin";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn91) {
  std::string src = "sqrt(-(-x^(-2)))";
  std::string check = "x 2 ~ ^ ~ ~ sqrt";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn92) {
  std::string src = "sqrt(-(-x^(-2)))";
  std::string check = "x 2 ~ ^ ~ ~ sqrt";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn93) {
  std::string src = "sqrt(-(-x^(-2)))";
  std::string check = "x 2 ~ ^ ~ ~ sqrt";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn94) {
  std::string src = "sqrt(-(-x^(-2)))";
  std::string check = "x 2 ~ ^ ~ ~ sqrt";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn95) {
  std::string src = "-X*2";
  std::string check = "x ~ 2 *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn96) {
  std::string src = "-X*2";
  std::string check = "x ~ 2 *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn97) {
  std::string src = "-X*2";
  std::string check = "x ~ 2 *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn98) {
  std::string src = "-X*2";
  std::string check = "x ~ 2 *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn99) {
  std::string src = "-X*2";
  std::string check = "x ~ 2 *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn100) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn101) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn102) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn103) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn104) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn105) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn106) {
  std::string src = "-X*PI";
  std::string check = "x ~ pi *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn107) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn108) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn109) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn110) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn111) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn112) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn113) {
  std::string src = "-X*E";
  std::string check = "x ~ e *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn114) {
  std::string src = "cos5";
  std::string check = "5 cos";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn115) {
  std::string src = "cos5 + 1";
  std::string check = "5 cos 1 +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn116) {
  std::string src = "cos5*2 + 5/2";
  std::string check = "5 cos 2 * 5 2 / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn117) {
  std::string src = "cossintan5*2 + 5/2";
  std::string check = "5 tan sin cos 2 * 5 2 / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn118) {
  std::string src = "cossintan(5*2)+ 5/2";
  std::string check = "5 2 * tan sin cos 5 2 / +";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn119) {
  std::string src = "cossin(tan(5*2)+ 5)/2";
  std::string check = "5 2 * tan 5 + sin cos 2 /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn120) {
  std::string src = "acos(-1+1) * cossin(tan(5*2)+ 5)/2";
  std::string check = "1 ~ 1 + acos 5 2 * tan 5 + sin cos * 2 /";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn121) {
  std::string src = "acos(-1+1) * cos(cossin(tan(5*2)+ 5)/2)";
  std::string check = "1 ~ 1 + acos 5 2 * tan 5 + sin cos 2 / cos *";

  TestGetRpnOk(src, check);
}

TEST(TestMathCalcModel, TestGetRpn122) {
  std::string src = "acos(-1+1) * cos(coscossinsin(tan(5*2)+ 5)/2) +5/2";
  std::string check =
      "1 ~ 1 + acos 5 2 * tan 5 + sin sin cos cos 2 / cos * 5 2 / +";

  TestGetRpnOk(src, check);
}

}  // namespace