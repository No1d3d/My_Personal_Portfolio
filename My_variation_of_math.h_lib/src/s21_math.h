#ifndef _S21_MATH_H_
#define _S21_MATH_H_

#define S21_EPS 1E-18

#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define MAX_ITER 1000

#define S21_PI 3.14159265358979323846L
#define S21_LOG2 0.6931471805599453L
#define S21_SQRT2 1.41421356237309504880L

int s21_isnan(double x);
int s21_isinf(double x);
int s21_signbit(double x);
int s21_sign(double x);

int s21_get_exp2(double x);         // x = mant * 2^exp, extract exp from x
long double s21_int_pow2(int exp);  // return long double with value 2^exp (int)
long double s21_pow2(double exp);   // 2^exp, exp > 0 and could be fraction

long double s21_pow0_2(double base,
                       double exp);  // returns a power of base from (0; 2)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif  // _S21_MATH_H_
