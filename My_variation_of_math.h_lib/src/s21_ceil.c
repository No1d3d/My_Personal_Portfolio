#include <limits.h>

#include "s21_math.h"

long double s21_ceil(double x) {
  long double res = x;
  if (!s21_isinf(x) && !s21_isnan(x)) {
    if (res < LLONG_MAX && res > (-LLONG_MAX - 1)) res = (long long)x;
    if (res < x) ++res;
  }
  return res;
}
