#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t i;
  char *res = s21_NULL;
  for (i = 0; i < s21_strlen(str2); i++) {
    char *ptr = s21_strchr(str1, str2[i]);
    if (ptr != s21_NULL) {
      res = ptr;
      break;
    }
  }
  return res;
}