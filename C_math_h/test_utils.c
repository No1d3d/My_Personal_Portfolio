#include "test_utils.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if __unix__
int is_nan_or_inf(long double x) { return isnanl(x) || isinfl(x); }
#else
int is_nan_or_inf(long double x) { return isnan(x) || isinf(x); }
#endif  // __unix__

int is_big_number(long double x) { return fabsl(x) > 1E10L; }

int is_noncomparable_with_eps(long double x) {
  return is_nan_or_inf(x) || is_big_number(x);
}

#ifdef MEASURE_TIME
static struct TimeTable timeTable[MAX_NUM_OF_FUNC];

static size_t func_num = 0;

size_t func_index(const char *func_name) {
  size_t i;
  for (i = 0; i < func_num; ++i) {
    if (strcmp(func_name, timeTable[i].func_name) == 0) break;
  }
  if (i == func_num) {
    strncpy(timeTable[i].func_name, func_name, MAX_NAME_LEN);
    timeTable[i].std_time = 0;
    timeTable[i].s21_time = 0;
    ++func_num;
  }
  return i;
}

void add_std_time(const char *func_name, double time) {
  size_t i = func_index(func_name);
  timeTable[i].std_time += time;
}

void add_s21_time(const char *func_name, double time) {
  size_t i = func_index(func_name);
  timeTable[i].s21_time += time;
}

void print_time_table() {
  puts("");
  puts("---------------------------------------------------");
  puts("Total time for each s21-function in comparison");
  puts("with the total time for the same std-function.");
  puts("---------------------------------------------------");
  puts("");
  printf("%-*s%-14.12s%-14.12s%-14.12s\n", MAX_NAME_LEN, "Function", "std, us",
         "s21, us", "s21/std");
  puts("---------------------------------------------------");
  for (size_t i = 0; i < func_num; ++i) {
    printf("%-*s%-14.f%-14.f%-14.1f\n", MAX_NAME_LEN, timeTable[i].func_name,
           timeTable[i].std_time, timeTable[i].s21_time,
           timeTable[i].s21_time / timeTable[i].std_time);
  }
  puts("---------------------------------------------------");
  puts("");
}
#endif  // MEASURE_TIME
