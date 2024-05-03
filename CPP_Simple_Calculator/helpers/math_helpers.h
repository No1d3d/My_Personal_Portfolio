#ifndef S21_SMART_CALC_V20_HELPERS_MATH_HELPERS_H_
#define S21_SMART_CALC_V20_HELPERS_MATH_HELPERS_H_

#include <string>  // std::string | std::to_string

namespace s21 {
namespace math_helpers {

double Round(double value, int precision);
double FinanceRound(const double value);
std::string HumanFormat(int value);
std::string HumanFormat(double value, int precision = 2);
std::string RemoveTrailingZeros(const std::string& input);
int GetDaysCount(int month, int year);

}  // namespace math_helpers
}  // namespace s21

#endif  // S21_SMART_CALC_V20_HELPERS_MATH_HELPERS_H_