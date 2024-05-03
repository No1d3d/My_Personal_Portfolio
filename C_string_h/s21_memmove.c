#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  const char *end;
  const char *string;
  char *destination;
  char *lastd;
  string = src;
  destination = dest;
  if (destination < string) {
    while (n--) *destination++ = *string++;
  } else {
    end = string + (n - 1);
    lastd = destination + (n - 1);
    while (n--) *lastd-- = *end--;
  }
  return (dest);
}