#include "s21_sscanf.h"

char *get_number_scan(char *f, int *value, int *err, crit s_tok) {
  char tmp_digit[4] = {'\0'};
  int k = 0;
  while (1) {
    if (is_number(*f)) {
      tmp_digit[k++] = *f;
    } else {
      break;
    }
    f++;
  }
  *value = s21_atoi_sscanf(tmp_digit, err, s_tok);
  return f;
}

void parse_fmt_and_record(const char *str, char *f, va_list *args, char *s,
                          int *success) {
  while (*f) {
    if (*f == '%') {
      f++;
      crit s_tok = {0, '0', '0', 0};
      if (is_number(*f)) {
        f = get_number_scan(f, &(s_tok.width), &(s_tok.err), s_tok);
      }
      if (*f == 'h' || *f == 'l' || *f == 'L') {
        s_tok.lenght = *f;
        f++;
      }
      char str_spec[16] = "cdieEfgGosuxXpn";
      int pos_f = *f;
      if (s21_strchr(str_spec, pos_f) != s21_NULL) {
        s_tok.specifier = *f;
        f++;
      }
      while (*s == '\n' || *s == '\t' || *s == ' ') s++;
      s = process_record(str, s_tok, args, s, success);
    } else
      f++;
  }
}

char *process_record(const char *str, crit s_tok, va_list *args, char *s,
                     int *success) {
  switch (s_tok.specifier) {
    case 'p':
    case 'x':
    case 'X':
    case 'o':
    case 'u':
    case 'i':
    case 'd':
      s = int_to_mem(s, s_tok, args, success);
      break;
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f':
      s = float_to_mem(s, s_tok, args, success);
      break;
    case 'c':
      s = char_to_mem(s, args, success);
      break;
    case 's':
      s = string_to_mem(s, args, success, s_tok);
      break;
    case 'n': {
      int *n = va_arg(*args, int *);
      *n = s - str - 1;
      break;
    }
    case '%':
      s++;
      break;
  }
  return s;
}

char *int_to_mem(char *s, crit s_tok, va_list *args, int *success) {
  char buf[256] = {"j"};
  int i = 0;
  while ((*s && *s != ' ') && (i < s_tok.width || s_tok.width == 0)) {
    if (*s == '*') {
      s_tok.width = va_arg(*args, int);
      if (s_tok.width == 0) {
        s_tok.err = 0;
      }
    }
    if (*s == '*' && s21_strchr("cdieEfgGosuxXpn", *(s++)) != s21_NULL) {
    }
    if (s21_strchr(".-+0123456789", *s) != s21_NULL) {
      buf[i] = *s;
      s++;
      i++;
    } else {
      s++;
    }
    if (*s == '.') {
      break;
    }
  }
  s++;
  i = 0;
  if (s_tok.lenght == 'h') {
    short int *value = va_arg(*args, short int *);
    *value = s21_atoi_sscanf(buf, &(s_tok.err), s_tok);
    if (s_tok.err) {
      *success += 1;
    }
  } else if (s_tok.lenght == 'l' &&
             s21_strchr("idouxX", s_tok.specifier) != s21_NULL) {
    unsigned long int *value = va_arg(*args, unsigned long int *);
    *value = s21_atoi_sscanf(buf, &(s_tok.err), s_tok);
    if (s_tok.err) {
      *success += 1;
    }
  } else if (s_tok.specifier == 'u' || s_tok.specifier == 'p') {
    unsigned long long int *value = va_arg(*args, unsigned long long int *);
    *value = s21_atoi_sscanf(buf, &(s_tok.err), s_tok);
    if (s_tok.err) {
      *success += 1;
    }
    if (*value == 0) {
      *success = -1;
    }
  } else if (s_tok.specifier == 'o' || s_tok.specifier == 'x' ||
             s_tok.specifier == 'X') {
    unsigned int *value = va_arg(*args, unsigned int *);
    *value = s21_atoi_sscanf(buf, &(s_tok.err), s_tok);
    if (s_tok.err) {
      *success += 1;
    }
  } else {
    int *value = va_arg(*args, int *);
    *value = s21_atoi_sscanf(buf, &(s_tok.err), s_tok);
    if (s_tok.err) {
      *success += 1;
    }
  }
  return s;
}

char *float_to_mem(char *s, crit s_tok, va_list *args, int *success) {
  char buf[256] = {"j"};
  int i = 0, dot = 2;
  while (*s && *s != ' ') {
    if (*s == '*') {
      s_tok.width = va_arg(*args, int);
    }
    if (s21_strchr("-+0123456789.", *s) != s21_NULL) {
      if (*s == '.') dot--;
      if (dot > 0) {
        buf[i] = *s;
        s++;
        i++;
      }
      if (s_tok.width != 0) {
        if (i == s_tok.width) {
          break;
        }
      }
    } else {
      s++;
    }
  }
  s++;
  i = 0;
  dot = 2;
  if (s_tok.lenght == 'L') {
    long double *value = va_arg(*args, long double *);
    *value = s21_atof_sscanf(buf, &(s_tok.err));
    if (s_tok.err) {
      *success += 1;
    }
  } else if (s_tok.lenght == 'l') {
    double *value = va_arg(*args, double *);
    *value = s21_atof_sscanf(buf, &(s_tok.err));
    if (s_tok.err) {
      *success += 1;
    }
  } else {
    float *value = va_arg(*args, float *);
    *value = s21_atof_sscanf(buf, &(s_tok.err));
    if (s_tok.err) {
      *success += 1;
    }
  }
  return s;
}

char *char_to_mem(char *s, va_list *args, int *success) {
  char buf = '0';
  buf = *s;
  s++;
  char *value = (char *)va_arg(*args, int *);
  if (value != s21_NULL) {
    *value = buf;
    *success += 1;
  }
  return s;
}

char *string_to_mem(char *s, va_list *args, int *success, crit s_tok) {
  char buf[256] = "0";
  int i = 0;
  while (*s && (i < s_tok.width || s_tok.width == 0)) {
    buf[i] = *s;
    i++;
    s++;
    if (*s == ' ' || *s == '\t' || *s == '\n') {
      s++;
      break;
    }
  }
  char *value = va_arg(*args, char *);
  if (value != s21_NULL) {
    s21_strcpy(value, buf);
    *success += 1;
  }
  return s;
}

char *clear_first_space(char *s) {
  while (*s == ' ') {
    s++;
  }
  return s;
}

int s21_isspace(char c) { return (c == ' ' || c == '\n' || c == '\t'); }

int check_EOF_str(const char *src, const char *fmt) {
  int res = -1;

  for (int i = 0; src[i]; i++) {
    if (!s21_isspace(src[i]) && src[i] != '\0') {
      res = 0;
      break;
    }
  }
  if (fmt[0] == '\0' || fmt[0] == '\n') {
    res = 0;
  }
  return res;
}

int s21_sscanf(const char *str, const char *fmt, ...) {
  va_list args;
  char *s = s21_NULL;
  char *f = s21_NULL;
  f = (char *)fmt;
  s = (char *)str;
  int success = 0;
  int EOF_str = check_EOF_str(str, fmt);
  va_start(args, fmt);
  s = clear_first_space(s);
  parse_fmt_and_record(str, f, &args, s, &success);
  va_end(args);
  return EOF_str ? EOF_str : success;
}

int s21_atoi_sscanf(const char *str, int *err, crit s_tok) {
  short int res_h = 0;
  long long int res = 0;
  long long int res_l = 0;
  unsigned short int res_uh = 0;
  unsigned int res_u = 0;
  int res_i = 0;
  int sign = 1, flag = 0;
  *err = 0;
  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    str++;
    *err = 1;
    flag = 1;
    if (*str == '\0') {
      break;
    }
  }
  res *= sign;
  res_h = (short int)res;
  res_l = res;
  res_uh = (unsigned short int)res;
  res_u = (unsigned int)res;
  res_i = (int)res;
  if (s_tok.lenght == 'h' && flag != 0) {
    if (res_h > 32765 || res_h < -32767) {
      *err = 0;
      if (res > 32765) {
        res_h = -1;
      } else {
        res_h = 0;
      }
    }
    res = res_h;
  } else if (s_tok.lenght == 'l' && flag != 0) {
    if (res > 9223372036854775807 || res < -9223372036854775807) {
      printf("HRE");
      if (res > 9223372036854775807) {
        res_l = -1;
      } else {
        res_l = 0;
      }
      *err = 0;
    }
    res = res_l;
  } else if (s_tok.specifier == 'u' && s_tok.lenght == 'h' && flag != 0) {
    if (res > 65535 || res < 0 || sign == -1) {
      *err = 0;
      if (res > 65535) {
        res_uh = -1;
      } else {
        res_uh = 0;
      }
    }
    res = res_uh;
  } else if (s_tok.specifier == 'u' && flag != 0) {
    if (res > 4294967295 || res < 0 || sign == -1) {
      *err = 0;
      if (res > 4294967295) {
        res_u = -1;
      } else {
        res_u = 0;
      }
    }
    res = res_u;
  } else {
    if (res > 2147483647 || res < -2147483647) {
      if (res > 2147483647) {
        res_i = -1;
      }
      if (sign == -1) {
        res_i = 0;
      }
    }
    res = res_i;
  }
  return res;
}

long double s21_atof_sscanf(const char *string, int *err) {
  double a, b, decimal_place = 0.0;
  int sign = 1;
  *err = 0;
  while (*string == ' ' || *string == '\n' || *string == '\t' ||
         *string == '\r' || *string == '\x0B' || *string == '\f') {
    string++;
  }
  if (*string == '+') {
    string++;
  }
  if (*string == '-') {
    sign = -1;
    string++;
  }
  for (a = 0; *string && is_number(*string); string++) {
    a = a * 10 + (*string - '0');
    *err = 1;
  }
  if (*string == '.') {
    string++;
  }
  for (decimal_place = 1.; *string && is_number(*string);
       string++, decimal_place *= 10.) {
    a = a * 10. + (*string - '0');
    *err = 1;
  }
  if (*string == 'e' || *string == 'E') {
    int esign = 1;
    if (a <= 1e-6) {
      a = 1;
    }
    string++;
    if (*string == '-') {
      esign = -1;
      string++;
    }
    if (*string == '+') {
      string++;
    }
    for (b = 0; *string && is_number(*string); string++) {
      b = b * 10 + (*string - '0');
    }
    b *= esign;
    *err = 1;
  } else {
    b = 0;
    *err = 1;
  }
  if ((*string == 'n' || *string == 'N') &&
      (string[1] == 'a' || string[1] == 'A') &&
      (string[2] == 'n' || string[2] == 'N')) {
    string += 3;
    a = NAN * sign;
    *err = 1;
  }
  if ((*string == 'i' || *string == 'I') &&
      (string[1] == 'n' || string[1] == 'N') &&
      (string[2] == 'f' || string[2] == 'F')) {
    string += 3;
    a = INFINITY * sign;
    *err = 1;
  }
  return (isnan(a) || isinf(a)) ? a : (a * sign / decimal_place) * powl(10, b);
}
