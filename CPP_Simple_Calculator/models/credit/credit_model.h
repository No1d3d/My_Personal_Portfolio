#ifndef S21_SMART_CALC_V20_MODELS_CREDIT_CREDIT_MODEL_H_
#define S21_SMART_CALC_V20_MODELS_CREDIT_CREDIT_MODEL_H_

#include "../finance_exception.h"

namespace s21 {

class CreditCalcModel final {
 public:
  enum PaymentsCreditTypes {
    kPaymentsAnnuity = 1,
    kPaymentsDifferentiated = 2,
  };

  const double kMinCreditSum = 0.01;
  const double kMaxCreditSum = 9999999999.99;
  const int kMinCreditMonths = 1;
  const int kMaxCreditMonths = 600;
  const double kMinCreditInterest = 0.01;
  const double kMaxCreditInterest = 999.0;

  CreditCalcModel() noexcept;
  CreditCalcModel(const CreditCalcModel& other) = delete;
  CreditCalcModel(CreditCalcModel&& other) = delete;
  CreditCalcModel& operator=(const CreditCalcModel& other) = delete;
  CreditCalcModel& operator=(CreditCalcModel&& other) = delete;
  ~CreditCalcModel() = default;

  void set_sum(double new_sum) noexcept {
    sum_ = new_sum;
    is_calculated_ = false;
  }
  void set_months(int new_months) noexcept {
    months_ = new_months;
    is_calculated_ = false;
  }
  void set_interest(double new_interest) noexcept {
    interest_ = new_interest;
    is_calculated_ = false;
  }
  void set_type(PaymentsCreditTypes new_type) noexcept {
    type_ = new_type;
    is_calculated_ = false;
  }

  double get_sum() const noexcept { return sum_; }
  int get_months() const noexcept { return months_; }
  double get_interest() const noexcept { return interest_; }
  PaymentsCreditTypes get_type() const noexcept { return type_; }
  bool get_is_calculated() const noexcept { return is_calculated_; }

  double get_payment_min() noexcept { return payment_min_; }
  double get_payment_max() noexcept { return payment_max_; }
  double get_overpayment() noexcept { return overpayment_; }
  double get_payment_total() noexcept { return payment_total_; }

  void CalculateCredit();

 private:
  void ResetModelResults() noexcept;
  void CalculateHandle() noexcept;
  void CheckModelData() const;
  inline bool CheckSum() const noexcept;
  inline bool CheckMonth() const noexcept;
  inline bool CheckInterest() const noexcept;

  double sum_;
  int months_;
  double interest_;
  PaymentsCreditTypes type_;

  bool is_calculated_;
  double payment_min_;
  double payment_max_;
  double overpayment_;
  double payment_total_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_CREDIT_CREDIT_MODEL_H_