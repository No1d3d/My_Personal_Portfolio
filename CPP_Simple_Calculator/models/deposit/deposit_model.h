#ifndef S21_SMART_CALC_V20_MODELS_DEPOSIT_DEPOSIT_MODEL_H_
#define S21_SMART_CALC_V20_MODELS_DEPOSIT_DEPOSIT_MODEL_H_

#include <vector>

#include "../finance_exception.h"

namespace s21 {

class DepositCalcModel final {
 public:
  struct DepositOperation {
    DepositOperation() noexcept : year(0), month(0), day(0), amount(0) {}
    DepositOperation(int year, int month, int day, double amount) noexcept
        : year(year), month(month), day(day), amount(amount) {}
    int year;
    int month;
    int day;
    double amount;
  };

  enum PaymentsPeriodicityDepositTypes {
    kPaymentsDay = 1,
    kPaymentsMonth = 2,
    kPaymentsEnd = 3,
  };

  const double kMinDepositSum = 0.01;
  const double kMaxDepositSum = 9999999999.99;
  const int kMinDepositMonths = 1;
  const int kMaxDepositMonths = 600;
  const double kMinDepositInterest = 0.01;
  const double kMaxDepositInterest = 999.0;
  const double kMinDepositTax = 0.0;
  const double kMaxDepositTax = 100.0;
  const int kMinDepositYear = 1900;
  const int kMaxDepositYear = 2100;

  DepositCalcModel() noexcept;
  DepositCalcModel(const DepositCalcModel& other) = delete;
  DepositCalcModel(DepositCalcModel&& other) = delete;
  DepositCalcModel& operator=(const DepositCalcModel& other) = delete;
  DepositCalcModel& operator=(DepositCalcModel&& other) = delete;
  ~DepositCalcModel() = default;

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
  void set_tax(double new_tax) noexcept {
    tax_ = new_tax;
    is_calculated_ = false;
  }
  void set_payments_periodicity(
      PaymentsPeriodicityDepositTypes new_payments_periodicity) noexcept {
    payments_periodicity_ = new_payments_periodicity;
    is_calculated_ = false;
  }
  void set_capitalization(bool new_capitalization) noexcept {
    capitalization_ = new_capitalization;
    is_calculated_ = false;
  }
  void set_date_start(int year, int month, int day) noexcept {
    year_start_ = year;
    month_start_ = month;
    day_start_ = day;
    is_calculated_ = false;
  }
  void AddOperation(int year, int month, int day, double amount) {
    operations_list_.push_back(DepositOperation{year, month, day, amount});
    is_calculated_ = false;
  }

  double get_sum() const noexcept { return sum_; }
  int get_months() const noexcept { return months_; }
  double get_interest() const noexcept { return interest_; }
  double get_tax() const noexcept { return tax_; }
  PaymentsPeriodicityDepositTypes get_payments_periodicity() const noexcept {
    return payments_periodicity_;
  }
  bool get_capitalization_type() const noexcept { return capitalization_; }
  bool get_year_start() const noexcept { return year_start_; }
  bool get_month_start() const noexcept { return month_start_; }
  bool get_day_start() const noexcept { return day_start_; }

  double get_interest_amount() const noexcept { return interest_amount_; }
  double get_deposit_amount() const noexcept { return deposit_amount_; }
  double get_tax_amount() const noexcept { return tax_amount_; }
  bool get_is_calculated() const noexcept { return is_calculated_; }

  void CalculateDeposit();
  void ClearOperationsList() noexcept {
    operations_list_.clear();
    is_calculated_ = false;
  }

 private:
  void ResetModelResults() noexcept;
  void CheckModelData() const;
  inline bool CheckSum() const noexcept;
  inline bool CheckSum(double sum) const noexcept;
  inline bool CheckMonth() const noexcept;
  inline bool CheckInterest() const noexcept;
  inline bool CheckTax() const noexcept;
  bool CheckDate(int year, int month, int day) const noexcept;
  void CheckOperations() const;
  void CalculateHandle();
  void OperationsHandle(int year, int month, int day, double& total_sum) const;

  double sum_;
  int months_;
  double interest_;
  double tax_;
  PaymentsPeriodicityDepositTypes payments_periodicity_;
  bool capitalization_;
  int year_start_;
  int month_start_;
  int day_start_;
  std::vector<DepositOperation> operations_list_;

  bool is_calculated_;
  double interest_amount_;
  double deposit_amount_;
  double tax_amount_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_DEPOSIT_DEPOSIT_MODEL_H_