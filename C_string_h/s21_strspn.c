#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *a, *b;
  size_t counter = 0;

  for (a = str1; *a != '\0'; ++a) {
    for (b = str2; *b != '\0'; ++b) {
      if (*a == *b) break;
    }
    if (*b == '\0') return counter;
    ++counter;
  }
  return counter;
}