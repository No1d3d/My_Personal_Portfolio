#include <gtest/gtest.h>

#include <chrono>
#include <cmath>
#include <string>
#include <vector>

#include "../models/math/math_model.h"

namespace {

const double kCalcEpsilon = 1e-7;

void TestCalculateOk(std::string src, double check) {
  s21::MathCalcModel model{src};
  model.Calculate();
  double result = model.get_result();
  EXPECT_NEAR(result, check, kCalcEpsilon);
}

void TestCalculateOkX(std::string src, double x, double check) {
  s21::MathCalcModel model{src};
  model.set_x_value(x);
  model.Calculate();
  double result = model.get_result();
  EXPECT_NEAR(result, check, kCalcEpsilon);
}

void TestCalculateNan(std::string src) {
  s21::MathCalcModel model{src};
  model.Calculate();
  double result = model.get_result();
  EXPECT_TRUE(std::isnan(result));
}

void TestCalculateInf(std::string src) {
  s21::MathCalcModel model{src};
  model.Calculate();
  double result = model.get_result();
  EXPECT_TRUE(std::isinf(result));
}

void TestCalculateFail(std::string src) {
  s21::MathCalcModel model{src};
  EXPECT_ANY_THROW(model.Calculate());
}

TEST(TestMathCalcModel, TestCalculatePedago1) {
  std::string src = "22+-+1";
  double check = 21;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago2) {
  std::string src = "22+-+-1";
  double check = 23;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago3) {
  std::string src = "22*-+1";
  double check = -22;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago4) {
  std::string src = "+-+1";
  double check = -1;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago5) {
  std::string src = "+-+1";
  double check = -1;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago6) {
  std::string src = "5 - (4 + 3) / (2 + 1)";
  double check = 2.66666666667;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago7) {
  std::string src = "5 + 1 + 8";
  double check = 14;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago8) {
  std::string src = "5 - 1 - 8";
  double check = -4;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago9) {
  std::string src = "5 * 1 * 8";
  double check = 40;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago10) {
  std::string src = "5 / 1 / 8";
  double check = 0.625;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago11) {
  std::string src = "2^1.5";
  double check = 2.82842712475;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago12) {
  std::string src = "2^1.5^1.5";
  double check = 3.57295391833;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago13) {
  std::string src = "2 mod 3";
  double check = 2;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago14) {
  std::string src = "0 mod 3";
  double check = 0;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago15) {
  std::string src = "5.57 mod 1.22";
  double check = 0.69;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago16) {
  std::string src = "-5.57 mod 1.22";
  double check = -0.69;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago17) {
  std::string src = "5.57 mod -1.22";
  double check = 0.69;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago18) {
  std::string src = "+(5-2) / +4";
  double check = 0.75;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago19) {
  std::string src = "-(5-2) / -(4-2)";
  double check = 1.5;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago20) {
  std::string src = "cos(0.785398163397448)";
  double check = 0.70710678118;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago21) {
  std::string src = "sin(0.785398163397448)";
  double check = 0.70710678118;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago22) {
  std::string src = "tan(0.785398163397448)";
  double check = 1.0;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago23) {
  std::string src = "acos(0.785398163397448)";
  double check = 0.667457216;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago24) {
  std::string src = "asin(0.785398163397448)";
  double check = 0.903339111;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago25) {
  std::string src = "atan(0.785398163397448)";
  double check = 0.66577375;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago26) {
  std::string src = "sqrt(0.785398163397448)";
  double check = 0.88622692545;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago27) {
  std::string src = "ln(0.785398163397448)";
  double check = -0.24156447527;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago28) {
  std::string src = "log(0.785398163397448)";
  double check = -0.10491011863;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago29) {
  std::string src = "-(-sin(1)^cos(1) + tan(1)/cos(1)) + atan(0)^log(10)";
  double check = -1.97151643705;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago30) {
  std::string src =
      "+sqrt(sqrt(3+78)-5) + sqrt((-3)^4) + (-5/(-asin(0) + acos(0)))";
  double check = 7.81690114;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago31) {
  std::string src =
      "(sqrt(cos(0.5))*cos(3000.5)+sqrt(0.5)-0.7)*(4-0.5*0.5)^0.01*sqrt(6-"
      "0.5^2)";
  double check = -2.17094355609;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago32) {
  std::string src =
      "log((-1)+4)^2*(3*(-1)^2-(-1)-1) + log((-1)^2+(-1)+1/(-1)^2-(-1)+1)";
  double check = 1.16005532984;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago33) {
  std::string src = "sin(0)*cos(0)-2*cos(0)^(0)+3*sin(0)^2*(0)";
  double check = -2;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago34) {
  std::string src =
      "(sin(3.14)*cos(3.14)*(sin(3.14) +cos(3.14)))*(tan(3.14) + "
      "sqrt(3.14^cos(3.14))-log(3.14^sin(3.14))) * 0 * "
      "(sin(3.14)*cos(3.14)*(sin(3.14) +cos(3.14)))";
  double check = 0;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago35) {
  std::string src = "(((((-(5-2)+7)+8-(9-7))-(9+7))+87-(99+1))-(-5))";
  double check = -14;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago36) {
  std::string src = "(5+5)/0";

  TestCalculateInf(src);
}

TEST(TestMathCalcModel, TestCalculatePedago37) {
  std::string src = "(5+5)/(5-5)";

  TestCalculateInf(src);
}

TEST(TestMathCalcModel, TestCalculatePedago38) {
  std::string src = "sqrt(5-7)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculatePedago39) {
  std::string src = "5.96 + 6.97 - 7.98 * 8.99";
  double check = -58.8102;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculatePedago40) {
  std::string src = "5..5 + 1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateNan1) {
  std::string src = "-5^-sin(-2)^-cos(-2) + -6^-sin(-2)^-cos(-2)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan2) {
  std::string src = "acos(10)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan3) {
  std::string src = "asin(10)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan4) {
  std::string src = "sqrt(-11.11)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan5) {
  std::string src = "ln(-1)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan6) {
  std::string src = "log(-1)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan7) {
  std::string src =
      "log(5.22)^-acos(-0.33)^-atan(-1) + "
      "-sqrt(10)*-asin(-0.33)^-acos(-0)/-6^-tan(-1)";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan8) {
  std::string src = "sin(-0.00001)^(-0.00001)^2";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateNan9) {
  std::string src = "sin(-3.1415)^(-3.1415)^2";

  TestCalculateNan(src);
}

TEST(TestMathCalcModel, TestCalculateInf1) {
  std::string src = "ln(0)";

  TestCalculateInf(src);
}

TEST(TestMathCalcModel, TestCalculateInf2) {
  std::string src = "log(0)";

  TestCalculateInf(src);
}

TEST(TestMathCalcModel, TestCalculateInf3) {
  std::string src = "5 + 1e400";

  TestCalculateInf(src);
}

TEST(TestMathCalcModel, TestCalculateFail00) {
  std::string src = "";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail000) {
  std::string src = "    ";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail1) {
  std::string src = "5*(5+1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail2) {
  std::string src = "5*(5+1(";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail3) {
  std::string src = "5*)5+1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail4) {
  std::string src = "5*)5+1)";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail5) {
  std::string src = "5(*))5+1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail6) {
  std::string src = "5(*))(5+1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail7) {
  std::string src = "5.5.5 + 1";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail8) {
  std::string src = "5 + 1 + gg";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail9) {
  std::string src = "c";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail10) {
  std::string src = "co";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail11) {
  std::string src = "cos";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail12) {
  std::string src = "cos-";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail13) {
  std::string src = "-";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail14) {
  std::string src = "--+--+-";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail101) {
  std::string src = "5*5*";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail102) {
  std::string src = "5 5 5*5*";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail103) {
  std::string src = "(5)(*)(5)(+)(1)";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail104) {
  std::string src = "* 2 + 5";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail105) {
  std::string src = "/ 2 + 5";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail106) {
  std::string src = "2 + 5 + ";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail107) {
  std::string src = "2            +        5                -                ";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail108) {
  std::string src = "^ 2 + 5";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail109) {
  std::string src = "% 2 + 5 %";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail110) {
  std::string src = "%";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail111) {
  std::string src = "-";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail112) {
  std::string src = "+";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail113) {
  std::string src = "*";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail114) {
  std::string src = "^";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculateFail115) {
  std::string src = "9/5(3 * 3)";

  TestCalculateFail(src);
}

TEST(TestMathCalcModel, TestCalculate1) {
  std::string src = "3.58 + 4 * 2 / 5^2";
  double check = 3.900000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate2) {
  std::string src = "3 + 4 * 2 / (1 - 5)^2";
  double check = 3.500000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate3) {
  std::string src =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double check = -30.072164948453608;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate4) {
  std::string src = "5^2^3";
  double check = 390625.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate5) {
  std::string src = "5.45-2*5^2^3+2^2^3 +1";
  double check = -780987.550000000046566;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate6) {
  std::string src = "1";
  double check = 1.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate7) {
  std::string src = "1/5^5";
  double check = 0.000320000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate8) {
  std::string src = "2 % 3";
  double check = 2.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate9) {
  std::string src = "2 % -3";
  double check = 2.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate10) {
  std::string src = "5 * 5 / 2 % 3";
  double check = 0.500000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate11) {
  std::string src = "(5 * 5 / 2) % (3 * 4 / 2)";
  double check = 0.500000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate12) {
  std::string src = "4 * 4 / 2 % 3 * 4 / 2";
  double check = 4.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate13) {
  std::string src = "2 mod 3";
  double check = 2.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate14) {
  std::string src = "2 mod -3";
  double check = 2.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate15) {
  std::string src = "(5 * 5 / 2) mod (3 * 4 / 2)";
  double check = 0.500000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate16) {
  std::string src = "4 * 4 / 2 mod 3 * 4 / 2";
  double check = 4.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate17) {
  std::string src = "5.12345679^25";
  double check = 548374113803143424.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate18) {
  std::string src = "5.1234567555555555^25";
  double check = 548374021636660096.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate19) {
  std::string src = "pi^e";
  double check = 22.459157718361045;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate20) {
  std::string src = "-pi^-e";
  double check = -0.044525267266923;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate21) {
  std::string src = "(-pi^-e + pi * e / pi) - pi*(-e*(cos(pi))) + sin(pi/2)";
  double check = -4.865977661481445;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate22) {
  std::string src = "sin(2+3*1.55)";
  double check = 0.358643853492800;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate23) {
  std::string src = "-5--5";
  double check = 0.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate24) {
  std::string src = "-5--5+-4";
  double check = -4.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate25) {
  std::string src = "-1/5^-5";
  double check = -3125.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate26) {
  std::string src = "2---5";
  double check = -3.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate27) {
  std::string src = "--5+(-5-7-(-7*7))";
  double check = 42.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate28) {
  std::string src = "+5+(+5-7-(+7*7))";
  double check = -46.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate29) {
  std::string src =
      "+15/-(7-(1+1))*-3-(-2+(+1+1))*-15/-(7--(200+1))*+3-(2+(1+1))*(15/"
      "-(7-(1+1))*3-(2+(1+1))+15/-(7-+(1+1))*3*-(2+(1+1)))";
  double check = -83.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate30) {
  std::string src =
      "+15/-(7-(1+1))*-3-(-2+(+1+1))*-15/-(7--(200^-2^-5+1))*+3-(2+(1+1))*(15/"
      "-(7-(1+1))*3-(2+(1+1))^+5+15/-(7-+(1^+2^+1+1))*3*-(2^-1+(1+1)))";
  double check = 4051.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate31) {
  std::string src = "+-+-+++7-+--++-+-+++--7";
  double check = 0.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate32) {
  std::string src = "+-+-+++7-+--++-+-+++---7";
  double check = 14.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate33) {
  std::string src =
      "-(2^2^3-(+-+-+++7-+--++-+-+++---7)/2^1^1^1^1) + "
      "(2^2^3-(+-+-+++7-+--++-+-+++---7)/2^-1^+1^-1^+1)";
  double check = -21.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate34) {
  std::string src = "5^-3^-4";
  double check = 0.980326495766518;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate35) {
  std::string src = "(5^-3)^-4";
  double check = 244140625.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate36) {
  std::string src = "-1^2";
  double check = -1.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate37) {
  std::string src = "(-1)^2";
  double check = 1.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate38) {
  std::string src = "2^-2";
  double check = 0.250000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate39) {
  std::string src = "1-(2^-2^-3^-4)^-2^3^-2";
  double check = -1.100680418905650;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate40) {
  std::string src = "5^-1.5^-2.333";
  double check = 0.535281993241309;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate41) {
  std::string src = "cos(5)";
  double check = 0.283662185463226;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate42) {
  std::string src = "cos(-5)";
  double check = 0.283662185463226;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate43) {
  std::string src = "-cos(5)";
  double check = -0.283662185463226;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate44) {
  std::string src = "sin(10)";
  double check = -0.544021110889370;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate45) {
  std::string src = "sin(-10)";
  double check = 0.544021110889370;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate46) {
  std::string src = "-sin(10)";
  double check = 0.544021110889370;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate47) {
  std::string src = "cos(5)+sin(10)";
  double check = -0.260358925426144;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate48) {
  std::string src = "5^sin(2)^cos(2) + 6^sin(2)^cos(2)";
  double check = 11.785566947370333;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate49) {
  std::string src = "-5^-sin(2)^-cos(2) + -6^-sin(2)^-cos(-2)";
  double check = -0.391550347031466;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate50) {
  std::string src = "tan(5)";
  double check = -3.380515006246586;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate51) {
  std::string src = "acos(0)";
  double check = 1.570796326794897;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate52) {
  std::string src = "asin(0)";
  double check = 0.000000000000000;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate53) {
  std::string src = "asin(0.5)";
  double check = 0.523598775598299;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate54) {
  std::string src = "atan(1)";
  double check = 0.785398163397448;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate55) {
  std::string src = "atan(-100)";
  double check = -1.560796660108231;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate56) {
  std::string src = "sqrt(11.11)";
  double check = 3.333166662499792;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate57) {
  std::string src = "ln(1000.998)";
  double check = 6.908752781311226;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate58) {
  std::string src = "log(1000.998)";
  double check = 3.000433209757209;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate59) {
  std::string src = "sin(cos(tan(-3.14)))";
  double check = 0.841470299555526;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate60) {
  std::string src = "-sin(-cos(-tan(-3.14)))";
  double check = 0.841470299555526;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate61) {
  std::string src =
      "log(5.22)^acos(0.33)^atan(1) + sqrt(10)*asin(0.33)^acos(0)/6^tan(1)";
  double check = 0.711136802604327;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate62) {
  std::string src =
      "log(5.22)^-acos(-0.33)^-atan(-1) + "
      "-sqrt(10)*-asin(0.33)^-acos(-0)/-6^-tan(-1)";
  double check = 0.659422354595572;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate63) {
  std::string src = "8/+9";
  double check = 0.88888888888888888888888888888888888888888888888888888;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate64) {
  std::string src = "2^3^2";
  double check = 512;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate65) {
  std::string src = "2^3^2";
  double check = 512;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate66) {
  std::string src = "2^2^3";
  double check = 256;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate67) {
  std::string src = "2^2^-1";
  double check = 1.41421356237;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate68) {
  std::string src = "2^-2^-1";
  double check = 0.70710678118;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate69) {
  std::string src = "-2^-2^-1";
  double check = -0.70710678118;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate70) {
  std::string src = "sin(1)^tan(1)";
  double check =
      0.7642850878801051164634430717037068239411114707253028262962711190;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculate71) {
  std::string src = "asin(0.123)^acos(0.32)";
  double check =
      0.0738315694372950433700054542510916913395745170539682802118572474;

  TestCalculateOk(src, check);
}

TEST(TestMathCalcModel, TestCalculateX1) {
  std::string src = "sin(x)";
  double x = 3.0;
  double check =
      0.1411200080598672221007448028081102798469332642522655841518826412;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX2) {
  std::string src = "(x)";

  TestCalculateOkX(src, 1.0, 1.0);
  TestCalculateOkX(src, -1.0, -1.0);
  TestCalculateOkX(src, 0.0, 0.0);
  TestCalculateOkX(src, 99.987777, 99.987777);
  TestCalculateOkX(src, 1.2E-2, 1.2E-2);
}

TEST(TestMathCalcModel, TestCalculateX3) {
  std::string src = "x^x^x/log(x)";
  double x = 3.0;
  double check =
      1.59825147371971496581558634902032241150222658184726110687295E13;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX4) {
  std::string src = "x^x^x/log(x)";
  double x = 3.0;
  double check =
      1.59825147371971496581558634902032241150222658184726110687295E13;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX5) {
  std::string src = "--5+(-5-x-(-x*7))";
  double x = 13.0;
  double check = 78.0;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX6) {
  std::string src = "siN(x)*Cos(X)";
  double x = 9.0;
  double check =
      -0.375493623385838051875078042223557265688804400007220448379952939;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX7) {
  std::string src = "(X)";

  TestCalculateOkX(src, 1.0, 1.0);
  TestCalculateOkX(src, -1.0, -1.0);
  TestCalculateOkX(src, 0.0, 0.0);
  TestCalculateOkX(src, 99.987777, 99.987777);
  TestCalculateOkX(src, 1.2E-2, 1.2E-2);
}

TEST(TestMathCalcModel, TestCalculateX8) {
  std::string src = "-(tAn(2.37^-X)  + Ln (-x / 5 + X)  * (X^-x)^X)";
  double x = 1.22;
  double check =
      -0.345809761767014236631533369932981606616504507451612118609357664;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX9) {
  std::string src = "X*SIN(X)";
  double x = 1e12;
  double check =
      -6.112387023768894981920204153246305664962417055934159031939e11;

  TestCalculateOkX(src, x, check);
}

TEST(TestMathCalcModel, TestCalculateX10) {
  std::string src = "sin(SIN(Sin(sIn(1/ln(x^123)))))";

  TestCalculateOkX(
      src, 1.1, 0.0848898990439235846118616160981899308627657347568651677559);
  TestCalculateOkX(
      src, 0.123,
      -0.003879610863685763088414537234107919214529589828752687384489816);
  TestCalculateOkX(
      src, 10.99999999,
      0.0033904812650695138781092367326292050083149694081158212362697753);
  TestCalculateOkX(
      src, 1.559999e1,
      0.0029593134368661499309206638120922748629049334961983820121063120);
}

TEST(TestMathCalcModel, TestCalculateX11) {
  std::string src = "sqrt(-(-x^(-2)))";

  TestCalculateOkX(
      src, 1.1,
      0.9090909090909090909090909090909090909090909090909090909090909090);
  TestCalculateOkX(
      src, 0.123,
      8.1300813008130081300813008130081300813008130081300813008130081300);
  TestCalculateOkX(
      src, 10.99999999,
      0.0909090909917355372652141247865582952605075411459159464962872240);
  TestCalculateOkX(
      src, 1.559999e1,
      0.0641026051939776884472361841257590549737531883033258354652791444);
}

TEST(TestMathCalcModel, TestCalculateX12) {
  std::string src = "-X*2";

  TestCalculateOkX(src, 1.1, -2.2);
  TestCalculateOkX(src, 5.99, -11.98);
  TestCalculateOkX(src, 0.0, 0.0);
  TestCalculateOkX(src, -1.1, 2.2);
  TestCalculateOkX(src, -5.99, 11.98);
}

TEST(TestMathCalcModel, TestCalculateX13) {
  std::string src = "-X*PI";

  TestCalculateOkX(
      src, 1000.9999,
      -3144.733932084117672721782180398444059131078149057540989285337439);
  TestCalculateOkX(
      src, 1.1,
      -3.455751918948772562308907721607453172616886339312616403072439051);
  TestCalculateOkX(
      src, 1.0,
      -3.141592653589793238462643383279502884197169399375105820974944592);
  TestCalculateOkX(src, 0.0, 0.0);
  TestCalculateOkX(
      src, -1.0,
      3.141592653589793238462643383279502884197169399375105820974944592);
  TestCalculateOkX(
      src, -1.1,
      3.455751918948772562308907721607453172616886339312616403072439051);
  TestCalculateOkX(
      src, -1000.9999,
      3144.733932084117672721782180398444059131078149057540989285337439);
}

TEST(TestMathCalcModel, TestCalculateX14) {
  std::string src = "-X*E";

  TestCalculateOkX(
      src, 1000.9999,
      -2720.999838459321434691124222795268024988754565068950164545977098);
  TestCalculateOkX(
      src, 1.1,
      -2.9901100113049497588963162184879287475329718030699555324636643904);
  TestCalculateOkX(
      src, 1.0,
      -2.7182818284590452353602874713526624977572470936999595749669676277);
  TestCalculateOkX(src, 0.0, 0.0);
  TestCalculateOkX(
      src, -1.0,
      2.7182818284590452353602874713526624977572470936999595749669676277);
  TestCalculateOkX(
      src, -1.1,
      2.9901100113049497588963162184879287475329718030699555324636643904);
  TestCalculateOkX(
      src, -1000.9999,
      2720.999838459321434691124222795268024988754565068950164545977098);
}

TEST(TestMathCalcModel, TestCalculateX15) {
  TestCalculateOkX(
      "cos5", 0,
      0.2836621854632262644666391715135573083344225922522159449303590665);
  TestCalculateOkX(
      "cos5 + 1", 0,
      1.2836621854632262644666391715135573083344225922522159449303590665);
  TestCalculateOkX(
      "cos5*2 + 5/2", 0,
      3.0673243709264525289332783430271146166688451845044318898607181331);
  TestCalculateOkX(
      "cossintan5*2 + 5/2", 0,
      4.4442549672486343836974427890564268434420047106860989595480981638);
  TestCalculateOkX(
      "cossintan(5*2)+ 5/2", 0,
      3.3231382120949740050942593317891582874499264403207787275492723946);
  TestCalculateOkX(
      "cossin(tan(5*2)+ 5)/2", 0,
      0.4146238145039822521554842909209172122083287562336115471972779403);
  TestCalculateOkX(
      "acos(-1+1) * cossin(tan(5*2)+ 5)/2", 0,
      0.6512895648245439024570504413688795227075883911500366031929948725);
  TestCalculateOkX(
      "acos(-1+1) * cos(cossin(tan(5*2)+ 5)/2)", 0,
      1.4376995023882964154316647275000194229924494450058444018443447337);
  TestCalculateOkX(
      "acos(-1+1) * cos(coscossinsin(tan(5*2)+ 5)/2) +5/2", 0,
      3.9856327245337778479506137000856725634376701377479975450283417763);
}

TEST(TestMathCalcModel, TestCalculateX16) {
  std::string src = "(1+2)*4*cos(x*7-2)+sin(2*x)";

  TestCalculateOkX(
      src, 0,
      -4.993762038565708643970818754009146277192009252906538689061799685);
  TestCalculateOkX(
      src, 1,
      4.3132436523843968689956899240744325427153260784744816075432818105);
  TestCalculateOkX(
      src, -1,
      -11.84286056944180555581555640008572857765842577028005741387636620);
  TestCalculateOkX(
      src, 3.1415,
      5.0006526529247729384537194014345066742090447471689024905814);
  TestCalculateOkX(
      src, -3.1415,
      4.9868693235822276891025060779323512069902553800761844578813829469);
  TestCalculateOkX(
      src, 10.99,
      10.719604536660865619755477015229796204522609560815431755967149338);
  TestCalculateOkX(
      src, -10.99,
      -11.10921896927322341834046321463745033294476329632362949985888868);
}

TEST(TestMathCalcModel, TestCalculateX17) {
  std::string src = "-sqrt(x^log(5-x))+ln(55/(2+x))";

  TestCalculateOkX(
      src, 0,
      3.3141860046725256092454707897331403712718080738456796430105355911);
  TestCalculateOkX(
      src, 0.0001,
      3.2741344058744826641092408576526083594023302220603233269713181725);
  TestCalculateOkX(
      src, 0.25,
      2.5708055826820084094657418153995886097437123358877512428137779499);
  TestCalculateOkX(
      src, 0.5,
      2.2936323758172639317924203663618458098354236603489189882845870688);
  TestCalculateOkX(
      src, 0.99,
      1.9150861110406193442269116967615894407353573466391269896482785597);
  TestCalculateOkX(
      src, 1,
      1.9087208965643612272674576742687912346998176503831854453965212669);
  TestCalculateOkX(
      src, 2.5,
      1.3032644115050948036775638203682459166124453343301057438589765904);
  TestCalculateOkX(
      src, 3.99,
      1.2142473592046415553633521494907126298326077158247047376604176553);
  TestCalculateOkX(
      src, 4.55,
      1.3589060253876355277913219850242557380220410861565829140474826264);
  TestCalculateOkX(
      src, 4.9,
      1.6240578221766316016217115050811423904700309471250631327372845257);
  TestCalculateOkX(
      src, 4.9999,
      2.0214357219454838359653050927960312315100446397014466662462664878);
}

TEST(TestMathCalcModel, TestCalculateX18) {
  std::string src = "-(3)*(-x-(7*(-(-(-(--7))))))";

  TestCalculateOkX(src, -9999, -30144);
  TestCalculateOkX(src, -1, -150);
  TestCalculateOkX(src, 0, -147);
  TestCalculateOkX(src, 1, -144);
  TestCalculateOkX(src, 9999, 29850);
}

TEST(TestMathCalcModel, TestCalculateX19) {
  std::string src = "100.235+x-(x+10)";

  double step = -5000;
  for (int i = 0; i < 10000; ++i) {
    TestCalculateOkX(src, step, 90.235);
    step += 1.123456789;
  }
}

TEST(TestMathCalcModel, TestCalculateX20) {
  std::string src = "sin(x)^x^2";

  TestCalculateOkX(src, 0, 1);
  TestCalculateOkX(
      src, 1,
      0.8414709848078965066525023216302989996225630607983710656727517099);
  TestCalculateOkX(
      src, -1,
      -0.841470984807896506652502321630298999622563060798371065672751709);
  TestCalculateOkX(
      src, 3.1415,
      1.5735255737020204703881037474239979719263072452629042274836e-40);
  TestCalculateOkX(
      src, 5,
      -0.350435276265107683495568074964438547911522039490881345275572448);
  TestCalculateOkX(
      src, -5,
      0.3504352762651076834955680749644385479115220394908813452755724487);
}

TEST(TestMathCalcModel, TestCalculateSet1) {
  s21::MathCalcModel model{"cos(x) + sin(x) / pi "};
  model.set_x_value(5);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), -0.02157289126, kCalcEpsilon);
  model.set_x_value(9);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), -0.77994887375, kCalcEpsilon);

  model.set_math_expression("pi + cos(x) + sin(x)");

  model.set_x_value(5);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 2.46633056439, kCalcEpsilon);
  model.set_x_value(9);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 2.64258087695, kCalcEpsilon);

  model.set_math_expression("pi + pi + pi");

  model.set_x_value(0);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 9.42477796077, kCalcEpsilon);
  model.set_x_value(5);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 9.42477796077, kCalcEpsilon);
  model.set_x_value(9);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 9.42477796077, kCalcEpsilon);

  model.set_math_expression("pi + pi + pi / pi + pi");

  model.set_x_value(0);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 10.42477796077, kCalcEpsilon);
  model.set_x_value(5);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 10.42477796077, kCalcEpsilon);
  model.set_x_value(9);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 10.42477796077, kCalcEpsilon);

  model.set_math_expression("acos (x) + asin (x)");

  model.set_x_value(0.785398163397448);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 1.57079633, kCalcEpsilon);
  model.set_x_value(1);
  model.Calculate();
  EXPECT_NEAR(model.get_result(), 1.57079633, kCalcEpsilon);
}

TEST(TestMathCalcModel, TestCalculateSpeed) {
  std::string src = "sin(x)*cos(x)-2*cos(x)^x+3*sin(x)^2*x";

  int num_values = 100000;
  double start_x = -1000000;
  double finish_x = 1000000;

  s21::MathCalcModel model{src};

  std::vector<double> x_values;
  std::vector<double> y_values;
  x_values.reserve(num_values);
  y_values.reserve(num_values);

  double step = (finish_x - start_x) / num_values;

  for (int i = 0; i < num_values; ++i) {
    x_values.push_back(start_x);
    start_x += step;
  }

  model.get_rpn_expression();

  auto x_begin = x_values.begin();
  auto x_end = x_values.end();

  auto start = std::chrono::steady_clock::now();

  while (x_begin != x_end) {
    model.set_x_value(*x_begin);
    model.Calculate();
    y_values.push_back(model.get_result());
    ++x_begin;
  }

  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << "Num of points: " << num_values << std::endl;
  std::cout << "Time: "
            << std::chrono::duration<double, std::milli>(diff).count() << "ms"
            << std::endl;
  std::cout.precision(10);
  std::cout.setf(std::ios::fixed);

  EXPECT_NEAR(y_values.back(), 2988128.6780684986, kCalcEpsilon);
}

}  // namespace
