#include "s21_math.h"

long double s21_sin(double x_rad) {
  long double x = x_rad;
  long double res;
  if (s21_isnan(x)) {
    res = x;
  } else if (s21_isinf(x)) {
    res = -S21_NAN;
  } else {
    // sin(x+2*N*PI) = sin(x)
    x = s21_fmod(x, 2 * S21_PI);

    long double a = x;
    long double s = 0;
    int i = 1;
    while (s21_fabs(a) > S21_EPS && i < MAX_ITER) {
      s = s + a;
      a = -a * x * x / ((2 * i + 1) * 2 * i);
      ++i;
    }
    res = s;
  }
  return res;
}
