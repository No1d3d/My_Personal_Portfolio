#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <stddef.h>

int is_nan_or_inf(long double x);
int is_big_number(long double x);
int is_noncomparable_with_eps(long double x);

// ------------------------------------------
// Measure time for std and s21_ functions
// and save and print it as a table.
// ------------------------------------------
#ifdef MEASURE_TIME

#define MAX_NUM_OF_FUNC 32
#define MAX_NAME_LEN 16

struct TimeTable {
  char func_name[MAX_NAME_LEN];
  double std_time;
  double s21_time;
};

size_t func_index(const char *func_name);
void add_std_time(const char *func_name, double time);
void add_s21_time(const char *func_name, double time);
void print_time_table();

#endif  // MEASURE_TIME

#define TEST_INT(func, value)           \
  {                                     \
    int std_res = func(value);          \
    int s21_res = s21_##func(value);    \
    ck_assert_int_eq(std_res, s21_res); \
  }

#define TEST_BOOL(func, value)               \
  {                                          \
    int std_res = func(value) ? 1 : 0;       \
    int s21_res = s21_##func(value) ? 1 : 0; \
    ck_assert_int_eq(std_res, s21_res);      \
  }

#define BUF_SIZE 64
#define S21_TEST_EPS 1E-6

#define TEST_EQ(value1, value2)                        \
  {                                                    \
    if (!isnan(value1) || !isnan(value2)) {            \
      if (is_noncomparable_with_eps(value1) ||         \
          is_noncomparable_with_eps(value2)) {         \
        char std_buf[BUF_SIZE], s21_buf[BUF_SIZE];     \
        sprintf(std_buf, "%.15LE", value1);            \
        sprintf(s21_buf, "%.15LE", value2);            \
        ck_assert_str_eq(std_buf, s21_buf);            \
      } else {                                         \
        long double eps = S21_TEST_EPS;                \
        ck_assert_ldouble_eq_tol(value1, value2, eps); \
      }                                                \
    }                                                  \
  }

#ifdef MEASURE_TIME
#define TEST_FLOAT(func, ...)                               \
  {                                                         \
    struct timespec start, stop;                            \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);        \
    long double std_res = func##l(__VA_ARGS__);             \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);         \
    double std_time = (stop.tv_sec - start.tv_sec) * 1e6 +  \
                      (stop.tv_nsec - start.tv_nsec) / 1e3; \
    add_std_time(#func, std_time);                          \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);        \
    long double s21_res = s21_##func(__VA_ARGS__);          \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);         \
    double s21_time = (stop.tv_sec - start.tv_sec) * 1e6 +  \
                      (stop.tv_nsec - start.tv_nsec) / 1e3; \
    add_s21_time(#func, s21_time);                          \
    TEST_EQ(std_res, s21_res)                               \
  }
#else
#define TEST_FLOAT(func, ...)                      \
  {                                                \
    long double std_res = func##l(__VA_ARGS__);    \
    long double s21_res = s21_##func(__VA_ARGS__); \
    TEST_EQ(std_res, s21_res)                      \
  }
#endif

#endif  // _TEST_UTILS_H_
