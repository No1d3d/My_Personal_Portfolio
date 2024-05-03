#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;

  if (S21_NULL != src && S21_NULL != str) {
    s21_size_t str_length = s21_strlen(str);
    s21_size_t src_length = s21_strlen(src);
    s21_size_t new_length = src_length + str_length;

    result = calloc(new_length + 1, sizeof(char));

    if (result) {
      for (s21_size_t i = 0, j = 0, m = 0; i < new_length; i++) {
        if (i < start_index || !str[m])
          result[i] = src[j++];
        else
          result[i] = str[m++];
      }
      result[new_length] = '\0';
    }
  } else if (str == S21_NULL && src != S21_NULL) {
    result = calloc(s21_strlen(src) + 1, sizeof(char));
    s21_strcpy(result, src);
  }
  return result;
}
