#include "math_helpers.h"

#include <cmath>  // std::pow | std::round

namespace s21 {
namespace math_helpers {

double Round(double value, int precision) {
  double koef = std::pow(10, precision);
  return (std::round(value * koef) / koef);
}

// Альтернативное округление через строки, есть отличия:
// Вариант выше округляет так:
// 1674.625 -> 1674.63
// Через строки округляет так:
// 1674.625 -> 1674.62
// Используем 1й вариант, чтобы совпадали результаты с calcus.ru
// #include <iomanip>  // setprecision
// #include <sstream>  // stringstream
// double Round(double value, int precision) {
//   std::stringstream ss;
//   ss << std::fixed << std::setprecision(precision) << value;
//   return std::stod(ss.str());
// }

/**
 * @brief Округление до двух знаков после запятой
 *
 * @param value Округляемое значение
 * @return double Округленный результат
 */
double FinanceRound(double value) { return Round(value, 2); }

std::string HumanFormat(int value) { return std::to_string(value); }

std::string HumanFormat(double value, int precision) {
  double tmp = Round(value, precision);
  std::string result = std::to_string(tmp);
  return RemoveTrailingZeros(result);
}

std::string RemoveTrailingZeros(const std::string& input) {
  std::string result{input};
  if (result.find('.') != std::string::npos) {
    result = result.substr(0, result.find_last_not_of('0') + 1);

    if (result.find('.') == result.size() - 1) {
      result = result.substr(0, result.size() - 1);
    }
  }
  return result;
}

/**
 * @brief
 * год является високосным в двух случаях: либо он кратен 4, но при этом не
 * кратен 100, либо кратен 400. Год не является високосным, если он не кратен 4,
 * либо он кратен 100, но при этом не кратен 400.
 * @param month
 * @param year
 * @return int
 */
int GetDaysCount(int month, int year) {
  return 31 - (102 / month & 1) -
         ((4 / month & 2) >> (!(year % 4) - !(year % 100) + !(year % 400)));
}

}  // namespace math_helpers
}  // namespace s21
