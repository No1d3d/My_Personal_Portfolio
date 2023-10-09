#include "s21_math.h"

long double s21_fmod(double x, double y) {
  if (s21_isinf(x) || y == 0 || s21_isnan(y))
    x = S21_NAN;
  else if (!s21_isinf(y))
    x = x - (long long)(x / y) * y;
  return x;
}
