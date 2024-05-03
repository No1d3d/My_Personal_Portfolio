#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *buf1 = str1;
  s21_size_t counter1 = 0;
  s21_size_t counter2 = s21_strlen(str1);
  while (*str2 != '\0') {
    while (*str1 != '\0') {
      if (*str1 != *str2) {
        str1++;
        counter1++;
      } else {
        break;
      }
    }
    str2++;
    if (counter1 <= counter2) {
      counter2 = counter1;
      counter1 = 0;
    }
    counter1 = 0;
    str1 = buf1;
  }
  return counter2;
}