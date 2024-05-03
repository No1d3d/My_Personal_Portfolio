#include "s21_math.h"

long double atan_1_1(double x) {
  long double res = x;
  long double a = x;
  int i = 1;
  while (s21_fabs(a) > S21_EPS && i < MAX_ITER) {
    a = -a * x * x * (2 * i - 1) / (2 * i + 1);
    res += a;
    ++i;
  }
  return res;
}

long double s21_atan(double x) {
  long double res = 0;
  if (s21_isnan(x)) {
    return x;
  } else if (x < 1 && x > -1 && x != 0) {
    res = atan_1_1(x);
  } else if (x == 0) {
    res = 0;
  } else if (x == 1) {
    res = S21_PI / 4;
  } else if (x == -1) {
    res = -S21_PI / 4;
  } else if (x > 1) {
    res = S21_PI / 2 - atan_1_1(1 / x);
  } else if (x < -1) {
    res = -S21_PI / 2 - atan_1_1(1 / x);
  }
  return res;
}