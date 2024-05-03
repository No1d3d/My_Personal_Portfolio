#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result_string = s21_NULL;
  if (s21_NULL != str) {
    s21_size_t length = s21_strlen(str);
    result_string = (char *)calloc(length + 1, sizeof(char));
    if (s21_NULL != result_string) {
      s21_size_t bias = 'a' - 'A';
      for (s21_size_t i = 0; i <= length; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result_string[i] = str[i] + bias;
        } else {
          result_string[i] = str[i];
        }
      }
      result_string[length] = '\0';
    }
  }
  return result_string;
}
