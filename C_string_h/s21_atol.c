#include "s21_string.h"

long long int s21_atol(const char* string) {
  int c = 0;
  long long int result = 0;
  while (*string == ' ' ||
         (*string == '\n') | (*string == '\r') | (*string == '\t')) {
    ++string;
  }
  c = (int)(unsigned char)*string++;
  int sign = c;
  if (c == '-' || c == '+') {
    c = (int)(unsigned char)*string++;
  }
  while ((c >= '0') & (c <= '9')) {
    result = 10 * result + (c - (int)'0');
    c = (int)(unsigned char)*string++;
  }
  return (sign == '-') ? -result : result;
}
