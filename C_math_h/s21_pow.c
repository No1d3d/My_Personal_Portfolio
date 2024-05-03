#include <assert.h>

#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double res;
  // Process all possible +/-INF and +/-NAN combos
  if (exp == 0.0) {
    return 1.0L;
  } else if (s21_isnan(base) && s21_isnan(exp)) {
    if (s21_signbit(base) && s21_signbit(exp))
      res = -S21_NAN;
    else
      res = +S21_NAN;
  } else if (s21_isnan(base)) {
    res = base;
  } else if (s21_isnan(exp)) {
    if (base == 1.0L)
      res = 1.0L;
    else
      res = exp;
  } else if (s21_isinf(base) && s21_isinf(exp)) {
    if (s21_signbit(exp)) {
      res = 0.0L;
    } else {
      res = S21_INF;
    }
  } else if (s21_isinf(base)) {
    res = exp > 0 ? base : 0.0L;
  } else if (s21_isinf(exp)) {
    if (base == 0.0L) {
      if (s21_sign(exp) == +1)
        res = 0.0L;
      else
        res = S21_INF;
    } else if (s21_fabs(base) == 1.0L) {
      res = 1.0L;
    } else if (s21_fabs(base) > 1.0L) {
      if (s21_sign(exp) == 1)
        res = S21_INF;
      else
        res = 0.0L;
    } else if (s21_fabs(base) < 1.0L) {
      if (s21_sign(exp) == 1)
        res = 0.0L;
      else
        res = S21_INF;
    }
  } else if (base < 0) {
    int i_exp = s21_floor(exp);
    if ((double)i_exp != exp) {
      res = -S21_NAN;
    } else {
      if (i_exp % 2 == 0) {
        res = s21_pow(-base, exp);
      } else {
        res = -s21_pow(-base, exp);
      }
    }
  } else if (base == 0) {
    res = 0.0L;
  } else if (exp < 0) {
    res = 1.0L / s21_pow(base, -exp);
  } else {
    // calculate pow
    int e2 = s21_get_exp2(base);
    long double b = base / s21_int_pow2(e2);
    long double s = s21_pow0_2(b, exp);
    res = s * s21_pow2(e2 * exp);
  }
  return res;
}

// works only for a base in interval (0; 2)
long double s21_pow0_2(double base, double exp) {
  assert(base > 0 && base < 2);
  long double res = 0;
  if (exp < 0) {
    res = 1.0L / s21_pow0_2(base, -exp);
  } else {
    long double x = base - 1;
    long double a = 1;
    long double s = 0;
    int i = 1;
    while (s21_fabs(a) > S21_EPS && i < MAX_ITER) {
      s += a;
      a *= x * (exp - i + 1) / i;
      ++i;
    }
    res = s;
  }
  return res;
}
