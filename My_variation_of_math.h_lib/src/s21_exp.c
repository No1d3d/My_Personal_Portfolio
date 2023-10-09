#include <float.h>

#include "s21_math.h"

long double s21_exp(double x) {
  long double res = 0;
  if (x != x)
    res = S21_NAN;
  else if (x == 0.0)
    res = 1;
  else if (x == -S21_INF)
    res = 0;
  else if (x == S21_INF)
    res = x;
  else if (x < 0)
    res = 1 / s21_exp(-x);
  else {
    long double add = 1;
    long double i = 1;
    res = 1;
    while (s21_fabs((double)add) > S21_EPS) {
      add *= x / i;
      i++;
      res += add;
      if (res > DBL_MAX) {
        res = S21_INF;
        break;
      }
    }
  }
  return res;
}
