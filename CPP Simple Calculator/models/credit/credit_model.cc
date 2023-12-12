#include "./credit_model.h"

#include <cmath>  // pow | isinf | isnan

#include "../../helpers/math_helpers.h"

namespace s21 {

CreditCalcModel::CreditCalcModel() noexcept
    : sum_(0),
      months_(0),
      interest_(0),
      type_(kPaymentsAnnuity),
      is_calculated_(false),
      payment_min_(0),
      payment_max_(0),
      overpayment_(0),
      payment_total_(0) {}

void CreditCalcModel::CalculateCredit() {
  ResetModelResults();
  CheckModelData();
  CalculateHandle();
}

void CreditCalcModel::ResetModelResults() noexcept {
  payment_min_ = 0;
  payment_max_ = 0;
  overpayment_ = 0;
  payment_total_ = 0;
}

void CreditCalcModel::CalculateHandle() noexcept {
  if (type_ == kPaymentsAnnuity) {
    double total_payment = 0;
    double overpayment = 0;
    double month_interest = interest_ / (100 * 12);
    double month_payment =
        sum_ * (month_interest +
                month_interest / (std::pow(month_interest + 1, months_) - 1));
    month_payment = math_helpers::FinanceRound(month_payment);

    total_payment = month_payment * months_;
    overpayment = total_payment - sum_;
    payment_min_ = month_payment;
    payment_max_ = month_payment;
    overpayment_ = overpayment;
    payment_total_ = total_payment;
  } else if (type_ == kPaymentsDifferentiated) {
    double month_payment_min =
        sum_ + 2 * sum_ * (kMaxCreditInterest / (12 * 100));
    double month_payment_max = 0;
    double total_payment = 0;
    double overpayment = 0;
    double payment_main = sum_ / months_;
    double month_interest = interest_ / (100 * 12);
    double sum_tmp = sum_;
    for (int i = 0; i < months_; i++) {
      double payment_add = sum_tmp * month_interest;
      sum_tmp -= payment_main;
      double month_payment =
          math_helpers::FinanceRound(payment_main + payment_add);
      total_payment += month_payment;

      if (month_payment > month_payment_max) {
        month_payment_max = month_payment;
      }
      if (month_payment < month_payment_min) {
        month_payment_min = month_payment;
      }
    }
    overpayment = total_payment - sum_;
    payment_min_ = month_payment_min;
    payment_max_ = month_payment_max;
    overpayment_ = overpayment;
    payment_total_ = total_payment;
  }

  is_calculated_ = true;
}
void CreditCalcModel::CheckModelData() const {
  if (!CheckSum()) {
    throw s21::FinanceSumException("Incorrect sum");
  }

  if (!CheckMonth()) {
    throw s21::FinanceMonthException("Incorrect month");
  }

  if (!CheckInterest()) {
    throw s21::FinanceInterestException("Incorrect interest");
  }
}

inline bool CreditCalcModel::CheckSum() const noexcept {
  return !(sum_ < kMinCreditSum || sum_ > kMaxCreditSum || std::isinf(sum_) ||
           std::isnan(sum_));
}

inline bool CreditCalcModel::CheckMonth() const noexcept {
  return !(months_ < kMinCreditMonths || months_ > kMaxCreditMonths);
}

inline bool CreditCalcModel::CheckInterest() const noexcept {
  return !(interest_ < kMinCreditInterest || interest_ > kMaxCreditInterest ||
           std::isinf(interest_) || std::isnan(interest_));
}

}  // namespace s21
