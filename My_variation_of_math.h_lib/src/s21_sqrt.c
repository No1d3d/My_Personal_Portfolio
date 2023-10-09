#include "s21_math.h"

long double s21_sqrt(double x) {
  long double res;
  if (x && s21_signbit(x)) {
    res = -S21_NAN;
  } else if (s21_isinf(x)) {
    res = x;
  } else if (x == 0.0) {
    res = 0.0L;
  } else {
    long double a = x;
    int exp2 = s21_get_exp2(a);
    if (exp2 % 2 != 0) --exp2;

    a /= s21_int_pow2(exp2);
    long double y = a / 2;
    int i = 0;
    while (s21_fabs(y * y - a) > S21_EPS && i < MAX_ITER) {
      y = (y + a / y) / 2;
      ++i;
    }
    res = y * s21_int_pow2(exp2 / 2);
  }
  return res;
}
