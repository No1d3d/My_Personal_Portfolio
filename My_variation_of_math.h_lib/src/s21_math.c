#include "s21_math.h"

#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

int s21_isnan(double x) { return x != x; }

int s21_isinf(double x) { return !s21_isnan(x) && x != 0 && x / x != x / x; }

int s21_signbit(double x) {
  uint64_t *i = (uint64_t *)&x;
  return (*i >> 63) != 0;
}

int s21_sign(double x) { return s21_signbit(x) ? -1 : 1; }

// x = mant * 2^exp, extract exp from x
int s21_get_exp2(double x) {
  uint64_t *i = (uint64_t *)&x;
  return ((*i >> 52) & 0x7ffL) - 1023;
}

// return long double with value 2^exp (int)
long double s21_int_pow2(int exp) {
  long double res;
  if (exp < 1024) {
    uint64_t bits = ((uint64_t)(exp + 1023) << 52);
    res = *(double *)&bits;
  } else if (exp < 32767) {
    int n = exp / 2;
    res = s21_int_pow2(n) * s21_int_pow2(exp - n);
  } else {
    res = S21_INF;
  }
  return res;
}

// 2^exp, exp > 0 and could be fraction
long double s21_pow2(double exp) {
  double base = S21_SQRT2;
  double i_exp = (long long)exp;
  double f_exp = exp - i_exp;
  long double x = s21_pow0_2(base, f_exp);
  return x * x * s21_int_pow2(i_exp);
}
