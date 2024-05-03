#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *buf1, *buf2;
  int res = 0;
  buf1 = str1, buf2 = str2;
  for (; n--; buf1++, buf2++) {
    if (*buf1 != *buf2) {
      res = (*buf1 - *buf2);
      break;
    }
  }
  return res;
}