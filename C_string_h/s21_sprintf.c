#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  st_format_item format_item = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char *str_begin = str;
  va_list args;
  va_start(args, format);
  char result[BUFF_SIZE] = {'\0'};  // аргумент преобрахованный в строку

  while (*format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
      continue;
    } else {
      format++;
      format_item.minus = 0;
      format_item.plus = 0;
      format_item.space = 0;
      format_item.nullik = 0;
      format_item.grill = 0;
      format_item.width = 0;
      format_item.precision = 0;
      format_item.precision_set = 0;
      format_item.length = 0;
      format_item.specifier = 0;
    }
    format = parse_flags(&format_item, format);
    format = parse_width(&format_item, format, args);
    if (*format == '.') {
      format++;
      format = parse_precision(&format_item, format, args);
      format_item.precision_set = 1;
    }
    format = parse_length(&format_item, format);
    format = parse_specifier(&format_item, format);

    s21_memset(result, '\0', BUFF_SIZE);
    arg_selector(format_item, result, args);
    str = add_to_string(str, result);
    // printf("here\n");

    // if (*result == 0) break;
    // printf("here\n");
    // вывода символов при спец n не производиться
    if (format_item.specifier == 'n') {
      int *res = va_arg(args, int *);
      *res = str - str_begin;
    }
  }
  *str = '\0';
  va_end(args);
  return str - str_begin;
}

const char *parse_flags(st_format_item *format_item, const char *format) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '-':
        format_item->minus = 1;
        break;
      case '+':
        format_item->plus = 1;
        break;
      case ' ':
        format_item->space = 1;
        break;
      case '0':
        format_item->nullik = 1;
        break;
      case '#':
        format_item->grill = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *parse_width(st_format_item *format_item, const char *format,
                        va_list args) {
  int width = 0;

  if (*format == '*') {
    width = va_arg(args, int);
    format++;
  } else {
    format = get_number(format, &width);
  }
  format_item->width = width;
  return format;
}

const char *parse_precision(st_format_item *format_item, const char *format,
                            va_list args) {
  int precision = 0;

  if (*format == '*') {
    precision = va_arg(args, int);
    format++;
  } else {
    format = get_number(format, &precision);
  }
  format_item->precision = precision;
  return format;
}

const char *get_number(const char *format, int *value) {
  char tmp_digit[4] = {'\0'};
  int k = 0;
  while (1) {
    if (is_number(*format)) {
      tmp_digit[k++] = *format;
    } else {
      break;
    }
    format++;
  }
  *value = atoi(tmp_digit);
  return format;
}

int is_number(char c) {
  int result = 0;
  if (c >= '0' && c <= '9') {
    result = 1;
  }
  return result;
}

const char *parse_length(st_format_item *format_item, const char *format) {
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    format_item->length = *format;
    format++;
  }
  return format;
}

const char *parse_specifier(st_format_item *format_item, const char *format) {
  if (is_specifier(*format)) {
    format_item->specifier = *format;
    format++;
  }
  return format;
}

int is_specifier(char ch) {
  int result = 0;
  if (ch == 'c' || ch == 'd' || ch == 'i' || ch == 'f' || ch == 's' ||
      ch == 'u' || ch == '%' || ch == 'o' || ch == 'g' || ch == 'G' ||
      ch == 'e' || ch == 'E' || ch == 'x' || ch == 'X' || ch == 'n' ||
      ch == 'p') {
    result = 1;
  }
  return result;
}

void arg_selector(st_format_item format_item, char *result, va_list args) {
  char temp[BUFF_SIZE] = {'\0'};
  char formated_temp[BUFF_SIZE] = {'\0'};
  if (format_item.specifier == 'c') {
    char_processing(result, args, format_item);
  } else if (format_item.specifier == 'd' || format_item.specifier == 'i') {
    int_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 'u') {
    u_int_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 's') {
    s_processing(result, args, format_item);
  } else if (format_item.specifier == 'f') {
    f_processing(result, format_item, args, temp);
  } else if (format_item.specifier == 'o') {
    octal_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 'p') {
    p_processing(result, args, format_item, temp, formated_temp);
  } else if (format_item.specifier == 'x' || format_item.specifier == 'X') {
    hex_processing(result, args, format_item, temp, formated_temp);
  } else if (format_item.specifier == 'g' || format_item.specifier == 'G') {
    g_G_processing(result, args, format_item, temp);
  } else if (format_item.specifier == 'e' || format_item.specifier == 'E') {
    e_E_processing(result, args, format_item, temp);
  } else if (format_item.specifier == '%') {
    result[0] = '%';  // !!!!
  }

  if (format_item.specifier == 'X' || format_item.specifier == 'E' ||
      format_item.specifier == 'G') {
    up(result);
  }
  //  printf("selector res = %s\n", result);
}

void up(char *temp) {
  while (*temp) {
    if (*temp >= 'a' && *temp <= 'z') *temp = *temp - 'a' + 'A';
    temp++;
  }
}

void char_processing(char *result, va_list args, st_format_item format_item) {
  // char temp[BUFF_SIZE] = {'\0'};
  if (format_item.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(args, wchar_t);
    do_wide_char(format_item, result, w_c);
  } else {
    char c = va_arg(args, int);
    if (c != 0) do_char(format_item, result, c);
    // flags_processing(result, format_item, temp);
    // else
    //   *result = '\0';
  }
}

void do_char(st_format_item format_item, char *result, char c_value) {
  if (c_value == 0) {
    *result = 0;
  } else {
    if (!format_item.minus && format_item.width) {
      for (int i = 0; i < format_item.width; i++) {
        result[i] = ' ';
        if (i == format_item.width - 1) result[i] = c_value;
      }
    } else if (format_item.width) {
      result[0] = c_value;
      for (int i = 1; i < format_item.width; i++) result[i] = ' ';
    } else {
      result[0] = c_value;
    }
  }
  // printf("char res = %s\n", result);
}

void do_wide_char(st_format_item format_item, char *result, wchar_t w_c) {
  if (!format_item.minus && format_item.width) {
    char tmp[BUFF_SIZE] = {'\0'};
    wcstombs(tmp, &w_c, BUFF_SIZE);
    for (size_t i = 0; i < format_item.width - s21_strlen(tmp); i++) {
      result[i] = ' ';
    }
    s21_strcat(result, tmp);
  } else if (format_item.width) {
    wcstombs(result, &w_c, BUFF_SIZE);
    for (int i = s21_strlen(result); i < format_item.width; i++) {
      result[i] = ' ';
    }
  } else {
    wcstombs(result, &w_c, BUFF_SIZE);
  }
}

void octal_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp) {
  int add_grill = 0;
  temp[0] = '0';
  long long octal_value = va_arg(args, long long);
  if (octal_value != 0 && format_item.grill) {
    add_grill = 1;
  }
  octal_to_string(octal_value, temp + add_grill);
  // printf("o to str = %s\n", temp);
  if (!(format_item.grill && format_item.precision_set &&
        format_item.precision == 0)) {
    precision_processing(format_item, temp, result);
    // printf("o pre = %s\n", result);
    flags_processing(result, format_item, formated_temp);
    // printf("o fla = %s\n", result);
  } else {
    s21_strcpy(result, temp);
  }
}

void octal_to_string(long long octal_value, char *result) {
  int k = 0;
  int add_sign = 0;

  if (octal_value < 0) {
    octal_value *= -1;
    add_sign = 1;
  }

  if (octal_value == 0) {
    result[k] = '0';
    k++;
  }

  while (octal_value > 0) {
    result[k] = octal_value % 8 + '0';
    octal_value = octal_value / 8;
    k++;
  }

  if (add_sign) {
    result[k] = '-';
    k++;
  }

  result[k] = '\0';

  reverse_array(result);
}

void int_processing(char *result, va_list args, char *temp,
                    st_format_item format_item, char *formated_temp) {
  if (format_item.length == 'h') {
    int d_value = va_arg(args, int);
    d_value = (short int)d_value;
    int_to_string(d_value, temp);
  } else if (format_item.length == 'l') {
    long int d_value = va_arg(args, long long int);
    // printf("int = %ld\n", d_value);
    int_to_string(d_value, temp);
    // printf("int = %s\n", temp);
  } else {
    int d_value = va_arg(args, int);
    int_to_string(d_value, temp);
  }

  precision_processing(format_item, temp, result);
  // printf("pre = %s\n", result);
  flags_processing(result, format_item, formated_temp);
  // printf("fla = %s\n", result);
}

void u_int_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp) {
  unsigned long long int u_value = va_arg(args, unsigned long long int);

  if (format_item.length == 'h') {
    u_value = (unsigned short int)u_value;
  } else if (format_item.length == 'l') {
    u_value = (unsigned long int)u_value;
  }

  u_int_to_string(u_value, temp);
  precision_processing(format_item, temp, result);
  // printf("pres res = %s\n", result);
  flags_processing(result, format_item, formated_temp);
  // printf("flag res = %s\n", result);
}

void p_processing(char *result, va_list args, st_format_item format_item,
                  char *temp, char *formated_temp) {
  unsigned long long int p_value = va_arg(args, unsigned long long int);

  if (format_item.length == 'h') {
    p_value = (unsigned short int)p_value;
  } else if (format_item.length == 'l') {
    p_value = (unsigned long int)p_value;
  }
  hex_u_int_to_string(p_value, temp);
  precision_processing(format_item, temp, result);
  add_hex_Ox(result, format_item);
  flags_processing(result, format_item, formated_temp);
}

void add_hex_Ox(char *value, st_format_item format_item) {
  if (format_item.specifier == 'p') {
    int is_s21_NULL = 0;
    if (value[0] == '0') {
      if ((((int)s21_strlen(value) < format_item.width) &&
           format_item.precision_set && format_item.precision == 0) ||
          (format_item.width == 0 && format_item.precision_set &&
           format_item.precision == 0))
        is_s21_NULL = 1;
    }
    s21_memmove(value + 2, value, s21_strlen(value));
    value[0] = '0';
    value[1] = 'x';
    if (is_s21_NULL) {
      value[2] = '\0';
    }
  } else {
    if (not_all_zeroes(value)) {
      s21_memmove(value + 2, value, s21_strlen(value));
      value[0] = '0';
      value[1] = 'x';
    }
  }
}

int not_all_zeroes(char *array) {
  int result = 0;
  while (*array) {
    if (*array != '0') {
      result = 1;
    }
    array++;
  }
  return result;
}

void hex_processing(char *result, va_list args, st_format_item format_item,
                    char *temp, char *formated_temp) {
  unsigned long long hex = va_arg(args, unsigned long long);
  if (format_item.length == 'h') {
    hex = (unsigned short)hex;
  } else if (format_item.length == 'l') {
    hex = (unsigned long long)hex;
  } else {
    hex = (unsigned)hex;
  }

  hex_u_int_to_string(hex, temp);

  precision_processing(format_item, temp, result);
  if (format_item.grill) {
    add_hex_Ox(result, format_item);
  }
  flags_processing(result, format_item, formated_temp);

  // printf("fl res = %s\n", result);
}

void s_processing(char *result, va_list args, st_format_item format_item) {
  if (format_item.length == 'l') {
    wchar_t *wstr = va_arg(args, wchar_t *);
    do_wide_string(format_item, result, wstr);
  } else {
    char *s_value = va_arg(args, char *);
    do_string(format_item, result, s_value);
  }
}

void do_string(st_format_item format_item, char *result, char *s_value) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, s_value);
  if (format_item.precision_set) {
    tmp[format_item.precision] = '\0';
  }

  int len = s21_strlen(tmp);
  int gap = format_item.width - len;

  if (!format_item.minus && gap > 0) {
    s21_memset(result, ' ', gap);
    s21_strcpy(result + gap, tmp);
  } else if (format_item.minus && gap > 0) {
    s21_strcpy(result, tmp);
    s21_memset(result + len, ' ', gap);
  } else {
    s21_strcpy(result, tmp);
  }
}

void do_wide_string(st_format_item format_item, char *result, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (format_item.precision_set) {
    tmp[format_item.precision] = '\0';
  }

  int len = s21_strlen(tmp);
  int gap = format_item.width - len;

  if (format_item.minus && gap > 0) {
    s21_strcpy(result, tmp);
    s21_memset(result + len, ' ', gap);
  } else if (gap > 0) {
    s21_memset(result, ' ', gap);
    s21_strcpy(result + gap, tmp);
  } else {
    s21_strcpy(result, tmp);
  }
}

void f_processing(char *result, st_format_item format_item, va_list args,
                  char *temp) {
  long double f_value = 0.0;
  if (format_item.length == 'L') {
    f_value = va_arg(args, long double);
  } else {
    f_value = va_arg(args, double);
  }
  if (!format_item.precision_set) {
    format_item.precision = 6;
  }
  double_to_string(f_value, format_item, result);
  // printf("res double = %s\n", result);
  flags_processing(result, format_item, temp);
}

void int_to_string(long long int_value, char *result) {
  int k = 0;
  int add_sign = 0;
  int flag = 0;

  if (int_value < 0) {
    int_value *= -1;
    add_sign = 1;
  }
  if (int_value < 0) {
    int_value -= 1;
    add_sign = 1;
    flag = 1;
  }

  if (int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (llabs(int_value) > 0) {
    result[k] = int_value % 10 + '0';
    // printf("resu [%d] = %c\n", k, result[k]);
    int_value = int_value / 10;
    k++;
  }

  if (add_sign) {
    result[k] = '-';
    k++;
  }

  reverse_array(result);

  if (flag) {
    // printf("here h\n");
    result[k - 1] += 1;
  }
}

void u_int_to_string(unsigned long long int u_int_value, char *result) {
  int k = 0;

  if (u_int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (u_int_value > 0) {
    result[k] = u_int_value % 10 + '0';
    u_int_value = u_int_value / 10;
    k++;
  }

  result[k] = '\0';

  reverse_array(result);
}

char *add_to_string(char *result, char *temp) {
  if (s21_NULL != temp && s21_NULL != result) {
    while (*temp) {
      *result = *temp;
      result++;
      temp++;
    }
    *result = '\0';
  }
  return result;
}

void hex_u_int_to_string(unsigned long long u_int_value, char *result) {
  int k = 0;
  char bukva = 0;

  if (u_int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (u_int_value != 0) {
    bukva = (u_int_value % 16);

    if (bukva < 10) {
      bukva = bukva + 48;
    } else {
      bukva = bukva + 87;
    }
    // printf("hex resu [%d] = %c\n", k, result[k]);
    result[k++] = bukva;
    u_int_value /= 16;
  }

  result[k] = '\0';

  reverse_array(result);
}

void double_to_string(long double double_value, st_format_item format_item,
                      char *result) {
  long double left = 0.;
  long double right = 0.;
  char *right_buf = s21_NULL;
  char *left_buf = s21_NULL;
  char *buf = s21_NULL;
  char sign = '\0';

  if (double_value < 0) {
    double_value *= -1;
    sign = '-';
  }
  if (double_value <= LDBL_MAX) {
    int next_num = 0;
    right = fmodl(double_value, 10.L);
    left = (double_value - right) / 10.L;
    left_buf = get_left_side(left);
    right_buf = get_right_side(right, &next_num, format_item);
    buf = sum_and_free(left_buf, right_buf);
    do_round(&buf, next_num, s21_NULL, s21_NULL);
  }

  do_add_sign(buf, sign);
  result = add_to_string(result, buf);
  free(buf);
}

char *get_left_side(long double num) {
  char *ascii_str = s21_NULL;
  char *reverse_str = s21_NULL;
  int buf_len = 0;
  int length = 0;
  long double tmp_num = 0;
  if (num < 0) {
    num *= -1;
  }
  tmp_num = num;
  while (tmp_num > 1) {
    buf_len += 1;
    tmp_num /= 10;
  }
  buf_len = (buf_len > 0) ? buf_len : 2;
  ascii_str = (char *)calloc((buf_len + 5), sizeof(char));
  reverse_str = (char *)calloc((buf_len + 5), sizeof(char));
  if (ascii_str && reverse_str) {
    while (num >= 1L) {
      int digit = 0;
      digit = (int)fmodl(num, 10);
      num /= 10;
      reverse_str[length++] = s21_digit_to_char(digit, 0);
    }
    reverse_str[length] = '\0';
    s21_invert_str(reverse_str, ascii_str);
  }
  if (reverse_str) {
    free(reverse_str);
  }
  return ascii_str;
}

char *get_right_side(long double num, int *next_digit,
                     st_format_item format_item) {
  char *ascii_str = s21_NULL;
  int length = 0;
  int digit = 0;
  int precision = -1;
  precision = (format_item.precision >= 0) ? format_item.precision : 6;

  if (num < 0) {
    num *= -1;
  }
  digit = floorl(num);
  num = (num - digit) * 10;
  ascii_str = (char *)calloc((precision + 5), sizeof(char));
  // ascii_str = (char *)malloc(sizeof(char) * (precision + 5));
  if (ascii_str) {
    ascii_str[length++] = s21_digit_to_char(digit, 0);
    if (precision > 0 || format_item.grill) {
      ascii_str[length++] = '.';
    }
    for (int i = 0; i < precision; i++) {
      digit = (floorl(num) >= 0) ? (int)floorl(num) : 0;
      num = (num - digit) * 10;
      ascii_str[length++] = s21_digit_to_char(digit, 0);
    }
    ascii_str[length] = '\0';
    *next_digit = (int)floorl(num);
  }
  return ascii_str;
}

void do_round(char **num_string, int next_digit, char *exp_sign,
              unsigned *u_exp) {
  if (*num_string && next_digit >= 5) {
    int not_rounded = 1;
    int position = s21_strlen(*num_string) - 1;
    while (position >= 0 && not_rounded) {
      if ((*num_string)[position] == '.') {
        position -= 1;
      }
      if ((*num_string)[position] == '9') {
        (*num_string)[position] = '0';
        position -= 1;
      } else {
        (*num_string)[position] = (char)((*num_string)[position] + 1);
        not_rounded = 0;
      }
    }
    if (position == -1) {
      char *tmp_ptr = s21_NULL;
      char *tmp_array = s21_NULL;
      int num_string_len = 0;
      num_string_len = s21_strlen(*num_string);
      tmp_array = (char *)calloc(num_string_len + 1, sizeof(char));
      if (tmp_array) {
        s21_strcpy(tmp_array, *num_string);
        tmp_ptr =
            (char *)realloc(*num_string, sizeof(char) * (num_string_len + 5));
        if (tmp_ptr) {
          tmp_ptr[0] = '1';
          tmp_ptr[1] = '\0';
          s21_strcat(tmp_ptr, tmp_array);
          if (u_exp) {
            if (*exp_sign == '-') {
              *u_exp = *u_exp - 1;
              if (*u_exp == 0) {
                *exp_sign = '+';
              }
            } else {
              *u_exp = *u_exp + 1;
            }
            tmp_ptr[2] = tmp_ptr[1];
            tmp_ptr[1] = '.';
            tmp_ptr[s21_strlen(tmp_ptr) - 1] = '\0';
          }
          *num_string = tmp_ptr;
        }
        free(tmp_array);
      }
    }
  }
}

char *sum_and_free(char *string1, char *string2) {
  char *buf = s21_NULL;
  if (string1 && string2) {
    buf = (char *)calloc((s21_strlen(string1) + s21_strlen(string2) + 2),
                         sizeof(char));
    if (buf) {
      s21_strcat(buf, string1);
      s21_strcat(buf, string2);
    }
  }
  if (string1) {
    free(string1);
  }
  if (string2) {
    free(string2);
  }
  return buf;
}

char s21_digit_to_char(int digit, int text_case) {
  char ch = '\0';
  if (digit >= 0 && digit < 10) {
    ch = (char)(digit + 48);  // 0 - 9
  } else if (digit >= 10 && digit < 36) {
    if (text_case == 0) {
      ch = (char)(digit + 87);  // a - z
    } else {
      ch = (char)(digit + 55);  // A - Z
    }
  }
  return ch;
}

void s21_invert_str(char *origin, char *inverted) {
  if (origin && inverted) {
    int length = 0;
    length = s21_strlen(origin);
    for (int i = 0; i < length; i++) {
      inverted[i] = origin[length - 1 - i];
    }
    inverted[length] = '\0';
  }
}

void do_add_sign(char *buf, char sign) {
  if (sign && *buf) {
    s21_memmove(buf + 1, buf, s21_strlen(buf));
    buf[0] = sign;
  }
}

void reverse_array(char *result) {
  char tmp = '\0';
  int len = s21_strlen(result);
  for (int i = 0; i < len / 2; i++) {
    tmp = result[i];
    result[i] = result[len - 1 - i];
    result[len - 1 - i] = tmp;
  }
}

int is_int_spec(char spec) {
  int result = 0;
  if (spec == 'i' || spec == 'u' || spec == 'd' || spec == 'o' || spec == 'x' ||
      spec == 'X') {
    result = 1;
  }
  return result;
}

void precision_processing(st_format_item format_item, char *value,
                          char *result) {
  int len = s21_strlen(value);
  int i = 0;
  int sign = 0;

  if (value[0] == '-' && format_item.specifier != 'u') {
    result[0] = '-';
    sign = 1;
  }

  if (len < format_item.precision + sign) {
    if (sign) s21_memmove(value, value + 1, len);
    while (format_item.precision + sign - len > 0) {
      if (!i && result[0] == '-') {
        i++;
        continue;
      }
      result[i] = '0';
      // printf("res [%d] = %c\n", i, result[i]);
      i++;
      format_item.precision--;
    }
  }

  add_to_string(result + i, value);

  if (format_item.precision_set && format_item.precision == 0 &&
      is_int_spec(format_item.specifier) && result[0] == '0') {
    result[0] = '\0';
  }
}

void flags_processing(char *value, st_format_item format_item, char *temp) {
  char formated_value[BUFF_SIZE + 1] = {'\0'};
  if (format_item.plus && !is_u_int_spec(format_item)) {
    temp[0] = value[0] == '-' ? value[0] : '+';
    add_to_string(temp + 1, value[0] == '-' ? value + 1 : value);
    add_to_string(value, temp);
  } else if (format_item.space && value[0] != '-' &&
             !is_u_int_spec(format_item)) {
    temp[0] = ' ';
    add_to_string(temp + 1, value);
    add_to_string(value, temp);
  }
  if (format_item.width > (int)s21_strlen(value)) {
    int i = format_item.width - s21_strlen(value);
    int sign = 0;
    if (!format_item.minus) {
      //            printf("t = %c: i = %d\n", value[0], i);
      if ((value[0] == '-' || value[0] == '+') && format_item.nullik) {
        sign = 1;
      }
      temp[0] = value[0];
      add_to_string(formated_value, value + sign);
      s21_memset(temp + sign, format_item.nullik ? '0' : ' ', i);
      // printf("t = %c\n", temp[0]);
      add_to_string(temp + i + sign, formated_value);
    } else {
      add_to_string(temp, value);
      s21_memset(temp + s21_strlen(temp), ' ', i);
    }
    add_to_string(value, temp);
  }
  // printf("flags res = %s\n", value);
}

int is_u_int_spec(st_format_item format_item) {
  int result = 0;
  if (format_item.specifier == 'u' || format_item.specifier == 'x' ||
      format_item.specifier == 'X' || format_item.specifier == 'p' ||
      format_item.specifier == 'o') {
    result = 1;
  }
  return result;
}

void e_E_processing(char *result, va_list args, st_format_item format_item,
                    char *temp) {
  long double value = 0.;
  if (format_item.length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  int power = 0;
  char sign = '0';
  if ((int)value == 0) {
    sign = '-';
  } else {
    sign = '+';
  }

  if ((int)value - value) {
    while ((int)value == 0) {
      power++;
      value *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)value / 10 != 0) {
    power++;
    value /= 10;
  }

  if (!format_item.precision_set) {
    format_item.precision = 6;
  }
  double_to_string(value, format_item, result);
  science_format(result, power, sign);
  flags_processing(result, format_item, temp);
}

void science_format(char *string, int power, char sign) {
  int length = s21_strlen(string);
  string[length] = 'e';
  string[length + 1] = sign;
  string[length + 3] = power % 10 + '0';
  power /= 10;
  string[length + 2] = power % 10 + '0';
  string[length + 4] = '\0';
}

void g_G_processing(char *result, va_list args, st_format_item format_item,
                    char *temp) {
  long double value = 0.;
  if (format_item.length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  if (!format_item.precision_set) {
    format_item.precision = 6;
  }
  if (format_item.precision == 0) format_item.precision = 1;
  int precision = format_item.precision;

  long double copy_value = value;
  int power = 0;
  if ((int)value - value) {
    while ((int)copy_value == 0) {
      power++;
      copy_value *= 10;
    }
  }
  if (power > 4) {
    format_item.precision = 0;
    g_G_double_to_string(copy_value, format_item, result);
  } else {
    format_item.precision = 10;
    g_G_double_to_string(value, format_item, result);
  }
  gG_precision(result, precision);
  if (power > 4) science_format(result, power, '-');
  remove_trailing_zeroes(result);
  flags_processing(result, format_item, temp);
}

void gG_precision(char *result, int precison) {
  int flag = 0;
  int sign_val = 0;
  size_t len = s21_strlen(result);
  for (size_t i = 0; i < len; i++) {
    if ((result[i] == '0' && !flag) || result[i] == '.')
      continue;
    else
      flag = 1;

    if (is_number(result[i]) && flag) {
      sign_val++;
    }
    if (sign_val == precison && i + 1 < len) {
      int temp = result[i + 1] == '.' ? 2 : 1;
      result[i] =
          result[i + temp] - '0' > 5 ? (char)(result[i] + 1) : result[i];
      result[i + 1] = '\0';
      break;
    }
  }
}

void remove_trailing_zeroes(char *result) {
  char *point = s21_strchr(result, '.');
  if (point) {
    for (int i = s21_strlen(result) - 1; result[i] != '.'; i--) {
      if (result[i] == '0')
        result[i] = '\0';
      else
        break;
    }
    if (point[1] == '\0') point[0] = '\0';
  }
}

void g_G_double_to_string(long double double_value, st_format_item format_item,
                          char *result) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  int neg = double_value < 0 ? 1 : 0;
  double_value = neg ? double_value * -1 : double_value;
  long double l = 0, r = modfl(double_value, &l);
  if (format_item.precision == 0) {
    l = roundl(double_value);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < format_item.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r);
  long long left = l;
  if (!right) {
    for (int i = 0; i < format_item.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((format_item.precision_set && format_item.precision != 0) || (int)r ||
      (!format_item.precision_set && double_value == 0) ||
      s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      result[i] = '-';
      i++;
    }
    result[i] = buff[idx + 1];
  }
}
