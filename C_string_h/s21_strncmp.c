#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  unsigned char a, b;
  while (n) {
    a = *str1++;
    b = *str2++;
    if (a != b) return a - b;
    if (!a) break;
    n--;
  }
  return 0;
}