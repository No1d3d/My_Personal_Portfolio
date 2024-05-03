#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result_string = s21_NULL;
  if (s21_NULL != src) {
    if (s21_NULL != trim_chars && *trim_chars) {
      s21_size_t start_index = s21_find_start_index(src, trim_chars);
      s21_size_t end_index = s21_find_end_index(src, trim_chars);
      s21_size_t result_length = labs((long long)(end_index - start_index));
      result_string = (char *)calloc(result_length + 1, sizeof(char));
      if (s21_NULL != result_string) {
        for (s21_size_t i = start_index; i <= end_index; i++) {
          result_string[i - start_index] = src[i];
        }
        result_string[result_length] = '\0';
      }
    } else {
      result_string = s21_trim(src, " \n\t\v\f\r");
    }
  }
  return result_string;
}

s21_size_t s21_find_start_index(const char *src, const char *trim_chars) {
  int flag = 1;
  s21_size_t start_index = 0;
  while (flag) {
    for (s21_size_t i = 0; i < s21_strlen(trim_chars); i++) {
      if (src[start_index] != trim_chars[i]) {
        flag = 0;
      } else {
        flag = 1;
        start_index++;
        break;
      }
    }
  }
  return start_index;
}

s21_size_t s21_find_end_index(const char *src, const char *trim_chars) {
  int flag = 1;
  s21_size_t end_index = s21_strlen(src);
  while (flag) {
    for (s21_size_t i = 0; i < s21_strlen(trim_chars); i++) {
      if (src[end_index - 1] != trim_chars[i]) {
        flag = 0;
      } else {
        flag = 1;
        end_index--;
        break;
      }
    }
  }
  return end_index;
}
