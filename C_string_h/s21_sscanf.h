#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// #define s21_UINT_MAX 18446744073709551614

typedef struct criteria {
  int width;
  char lenght;
  char specifier;
  int err;
} crit;

int is_number(char c);
char *get_number_scan(char *f, int *value, int *err, crit s_tok);
void parse_fmt_and_record(const char *str, char *f, va_list *args, char *s,
                          int *success);
char *process_record(const char *str, crit s_tok, va_list *args, char *s,
                     int *success);
char *int_to_mem(char *s, crit s_tok, va_list *args, int *success);
char *float_to_mem(char *s, crit s_tok, va_list *args, int *success);
char *char_to_mem(char *s, va_list *args, int *success);
char *string_to_mem(char *s, va_list *args, int *success, crit s_tok);
char *clear_first_space(char *s);
int s21_isspace(char c);
int check_EOF_str(const char *src, const char *fmt);
int s21_atoi_sscanf(const char *str, int *err, crit s_tok);
int s21_sscanf(const char *str, const char *fmt, ...);

#endif  // S21_SSCANF_H
