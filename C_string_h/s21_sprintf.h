#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdarg.h>

// нужно реализовать atoi
// используется стандартный memset
///////////////////
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
/////////////////

typedef struct {
  //  flags
  int minus;
  int plus;
  int space;
  int grill;
  int nullik;
  ////
  int width;
  ////
  int precision;
  int precision_set;
  ////
  char length;
  ////
  char specifier;

} st_format_item;

int s21_sprintf(char *str, const char *format, ...);

const char *parse_flags(st_format_item *format_item, const char *format);

const char *parse_width(st_format_item *format_item, const char *format,
                        va_list args);

const char *parse_precision(st_format_item *format_item, const char *format,
                            va_list args);

const char *get_number(const char *format, int *value);

int is_number(char c);

const char *parse_length(st_format_item *format_item, const char *format);

const char *parse_specifier(st_format_item *format_item, const char *format);

int is_specifier(char ch);

void arg_selector(st_format_item format_item, char *result, va_list args);

void up(char *temp);

void up(char *temp);

void char_processing(char *result, va_list args, st_format_item format_item);

void do_char(st_format_item args, char *result, char c_value);

void do_wide_char(st_format_item format_item, char *result, wchar_t w_c);

void octal_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp);

void octal_to_string(long long octal_value, char *result);

void octal_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp);

void octal_to_string(long long octal_value, char *result);

void int_processing(char *result, va_list args, char *temp,
                    st_format_item format_item, char *formated_temp);

void u_int_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp);

void p_processing(char *result, va_list args, st_format_item format_item,
                  char *temp, char *formated_temp);

void add_hex_Ox(char *value, st_format_item format_item);

int not_all_zeroes(char *array);

void p_processing(char *result, va_list args, st_format_item format_item,
                  char *temp, char *formated_temp);

void add_hex_Ox(char *value, st_format_item format_item);

int not_all_zeroes(char *array);

void s_processing(char *result, va_list args, st_format_item format_item);

void do_string(st_format_item format_item, char *result, char *s_value);

void do_wide_string(st_format_item format_item, char *result, wchar_t *wstr);

void f_processing(char *result, st_format_item format_item, va_list args,
                  char *temp);

void int_to_string(long long int_value, char *result);

int is_int_sign(long long value);

void u_int_to_string(unsigned long long int_value, char *result);

void hex_processing(char *result, va_list args, st_format_item format_item,
                    char *temp, char *formated_temp);

void hex_u_int_to_string(unsigned long long u_int_value, char *result);

int is_int_sign(long long value);

void u_int_to_string(unsigned long long int_value, char *result);

void hex_processing(char *result, va_list args, st_format_item format_item,
                    char *temp, char *formated_temp);

void hex_u_int_to_string(unsigned long long u_int_value, char *result);

char *add_to_string(char *result, char *temp);

void double_to_string(long double double_value, st_format_item format_item,
                      char *result);

char *get_left_side(long double num);

char *get_right_side(long double num, int *next_digit,
                     st_format_item format_item);

void do_round(char **num_string, int next_digit, char *exp_sign,
              unsigned *u_exp);

char *sum_and_free(char *string1, char *string2);

char s21_digit_to_char(int digit, int text_case);

void s21_invert_str(char *origin, char *inverted);

void do_add_sign(char *buf, char sign);

void reverse_array(char *result);

void precision_processing(st_format_item format_item, char *value,
                          char *result);

int is_int_spec(char spec);

void flags_processing(char *result, st_format_item format_item, char *temp);

int is_u_int_spec(st_format_item format_item);

void e_E_processing(char *result, va_list args, st_format_item format_item,
                    char *temp);

void science_format(char *string, int power, char sign);

void g_G_processing(char *result, va_list args, st_format_item format_item,
                    char *temp);

void gG_precision(char *result, int precision);

void remove_trailing_zeroes(char *result);
void remove_trailing_zeroes(char *result);

void g_G_double_to_string(long double double_value, st_format_item format_item,
                          char *result);
void g_G_double_to_string(long double double_value, st_format_item format_item,
                          char *result);

#endif  //  SRC_S21_SPRINTF_H_
