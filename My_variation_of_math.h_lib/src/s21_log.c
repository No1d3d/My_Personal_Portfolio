#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#include "s21_math.h"

long double log_1_(double x) {
  x -= 1;
  long double res = 0;
  long double a = x;
  int i = 1;
  while (s21_fabs(a) > S21_EPS && i < MAX_ITER) {
    res += a;
    a = -a * x * i / (i + 1);
    ++i;
  }
  return res;
}

long double s21_log(double x) {
  long double res;
  if (s21_isnan(x)) {
    res = x;
  } else if (s21_isinf(x)) {
    if (s21_sign(x) == +1)
      res = x;
    else
      res = S21_NAN;
  } else if (x < 0) {
    res = S21_NAN;
  } else if (x == 0.0) {
    res = -S21_INF;
  } else {
    int e2 = s21_get_exp2(x);
    long double b = x / s21_int_pow2(e2);
    if (b > 1.5) {
      b /= 2;
      ++e2;
    }
    long double s = log_1_(b);
    res = s + e2 * S21_LOG2;
  }
  return res;
}