#include "./deposit_model.h"

#include <cmath>  // isnan | isinf | fabs

#include "../../helpers/math_helpers.h"

namespace s21 {

DepositCalcModel::DepositCalcModel() noexcept
    : sum_(0),
      months_(0),
      interest_(0),
      tax_(0),
      payments_periodicity_(),
      capitalization_(false),
      year_start_(0),
      month_start_(0),
      day_start_(0),
      operations_list_({}),
      is_calculated_(false),
      interest_amount_(0),
      deposit_amount_(0),
      tax_amount_(0) {}

void DepositCalcModel::CalculateDeposit() {
  ResetModelResults();
  CheckModelData();
  CalculateHandle();
}

void DepositCalcModel::ResetModelResults() noexcept {
  interest_amount_ = 0;
  deposit_amount_ = 0;
  tax_amount_ = 0;
}

void DepositCalcModel::CheckModelData() const {
  if (!CheckSum()) {
    throw FinanceSumException("Incorrect sum");
  }

  if (!CheckMonth()) {
    throw FinanceMonthException("Incorrect month");
  }

  if (!CheckInterest()) {
    throw FinanceInterestException("Incorrect interest");
  }

  if (!CheckTax()) {
    throw FinanceTaxException("Incorrect tax");
  }

  CheckOperations();
}

inline bool DepositCalcModel::CheckSum() const noexcept {
  return CheckSum(sum_);
}

inline bool DepositCalcModel::CheckSum(double sum) const noexcept {
  return !(sum < kMinDepositSum || sum > kMaxDepositSum || std::isinf(sum) ||
           std::isnan(sum));
}

inline bool DepositCalcModel::CheckMonth() const noexcept {
  return !(months_ < kMinDepositMonths || months_ > kMaxDepositMonths);
}

inline bool DepositCalcModel::CheckInterest() const noexcept {
  return !(interest_ < kMinDepositInterest || interest_ > kMaxDepositInterest ||
           std::isinf(interest_) || std::isnan(interest_));
}

inline bool DepositCalcModel::CheckTax() const noexcept {
  return !(tax_ < kMinDepositTax || tax_ > kMaxDepositTax || std::isinf(tax_) ||
           std::isnan(tax_));
}

bool DepositCalcModel::CheckDate(int year, int month, int day) const noexcept {
  if (year < kMinDepositYear || year > kMaxDepositYear) {
    return false;
  } else if (month < 1 || month > 12) {
    return false;
  } else if (day < 1 || day > 31) {
    return false;
  } else if (day > math_helpers::GetDaysCount(month, year)) {
    return false;
  }

  return true;
}

void DepositCalcModel::CheckOperations() const {
  if (operations_list_.size() > 0) {
    for (int i = 0; i < static_cast<int>(operations_list_.size()); ++i) {
      if (!CheckSum(std::fabs(operations_list_[i].amount))) {
        if (std::signbit(operations_list_[i].amount)) {
          throw FinanceSumOperationMinusException("Incorrect operations sum");
        } else {
          throw FinanceSumOperationPlusException("Incorrect operations sum");
        }
      }

      if (!CheckDate(operations_list_[i].year, operations_list_[i].month,
                     operations_list_[i].day)) {
        if (std::signbit(operations_list_[i].amount)) {
          throw FinanceDateOperationMinusException("Incorrect operations sum");
        } else {
          throw FinanceDateOperationPlusException("Incorrect operations sum");
        }
      }
    }
  }
}

void DepositCalcModel::CalculateHandle() {
  int start_year = year_start_;
  int start_month = month_start_;
  int start_day = day_start_;

  if (!CheckDate(start_year, start_month, start_day)) {
    throw s21::FinanceDateStartException("Incorrect start date");
  }

  double total_interest_payments = 0;
  double total_sum = sum_;
  double total_tax = 0;
  double pd = interest_ / (100 * 365);
  double pdv = interest_ / (100 * 366);

  int counter = months_;

  while (counter >= 0) {
    int num_days = math_helpers::GetDaysCount(start_month, start_year);
    int payment_days = 0;
    double month_sum = 0;
    for (int day = 1; day <= num_days; day++) {
      if (total_sum < 0) {
        throw FinanceOperationNoMoneyException("No money");
      }

      if (counter == months_) {
        if (day <= start_day) {
          if (day == start_day) {
            OperationsHandle(start_year, start_month, day, total_sum);
          }
          continue;
        }
      }

      if (counter == 0) {
        if (day > start_day) {
          continue;
        }
      }

      double percent_sum;
      if (math_helpers::GetDaysCount(2, start_year) == 29) {
        percent_sum = pdv * total_sum;
      } else {
        percent_sum = pd * total_sum;
      }

      if (payments_periodicity_ == kPaymentsDay) {
        percent_sum = math_helpers::FinanceRound(percent_sum);
        if (capitalization_ == true) {
          total_sum += percent_sum;
        }
      }
      month_sum += percent_sum;
      ++payment_days;

      OperationsHandle(start_year, start_month, day, total_sum);
    }

    if (payments_periodicity_ == kPaymentsMonth) {
      month_sum = math_helpers::FinanceRound(month_sum);
      if (capitalization_ == true) {
        total_sum += month_sum;
      }
    }

    total_interest_payments += month_sum;

    ++start_month;
    if (start_month == 13) {
      start_month = 1;
      ++start_year;
    }
    --counter;
  }

  if (payments_periodicity_ == kPaymentsEnd) {
    total_interest_payments =
        math_helpers::FinanceRound(total_interest_payments);
    if (capitalization_ == true) {
      total_sum += total_interest_payments;
    }
  }

  total_tax =
      math_helpers::FinanceRound(total_interest_payments * (tax_ / 100));

  interest_amount_ = total_interest_payments;
  deposit_amount_ = total_sum;
  tax_amount_ = total_tax;
  is_calculated_ = true;
}

void DepositCalcModel::OperationsHandle(int year, int month, int day,
                                        double &total_sum) const {
  if (operations_list_.size() > 0) {
    for (int i = 0; i < static_cast<int>(operations_list_.size()); ++i) {
      if (year == operations_list_[i].year &&
          month == operations_list_[i].month &&
          day == operations_list_[i].day) {
        total_sum += operations_list_[i].amount;
      }
    }
  }
}

}  // namespace s21
