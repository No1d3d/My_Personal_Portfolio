#ifndef S21_SMART_CALC_V20_MODELS_FINANCE_EXCEPTION_H_
#define S21_SMART_CALC_V20_MODELS_FINANCE_EXCEPTION_H_

#include <stdexcept>

namespace s21 {

class FinanceException : public std::logic_error {
 public:
  explicit FinanceException(const char* arg) : logic_error(arg){};
  virtual ~FinanceException() = default;
};

class FinanceSumException : public FinanceException {
 public:
  explicit FinanceSumException(const char* arg) : FinanceException(arg){};
  virtual ~FinanceSumException() = default;
};

class FinanceMonthException : public FinanceException {
 public:
  explicit FinanceMonthException(const char* arg) : FinanceException(arg){};
  virtual ~FinanceMonthException() = default;
};

class FinanceInterestException : public FinanceException {
 public:
  explicit FinanceInterestException(const char* arg) : FinanceException(arg){};
  virtual ~FinanceInterestException() = default;
};

class FinanceTaxException : public FinanceException {
 public:
  explicit FinanceTaxException(const char* arg) : FinanceException(arg){};
  virtual ~FinanceTaxException() = default;
};

class FinanceDateStartException : public FinanceException {
 public:
  explicit FinanceDateStartException(const char* arg) : FinanceException(arg){};
  virtual ~FinanceDateStartException() = default;
};

class FinanceDateOperationPlusException : public FinanceException {
 public:
  explicit FinanceDateOperationPlusException(const char* arg)
      : FinanceException(arg){};
  virtual ~FinanceDateOperationPlusException() = default;
};

class FinanceDateOperationMinusException : public FinanceException {
 public:
  explicit FinanceDateOperationMinusException(const char* arg)
      : FinanceException(arg){};
  virtual ~FinanceDateOperationMinusException() = default;
};

class FinanceSumOperationPlusException : public FinanceException {
 public:
  explicit FinanceSumOperationPlusException(const char* arg)
      : FinanceException(arg){};
  virtual ~FinanceSumOperationPlusException() = default;
};

class FinanceSumOperationMinusException : public FinanceException {
 public:
  explicit FinanceSumOperationMinusException(const char* arg)
      : FinanceException(arg){};
  virtual ~FinanceSumOperationMinusException() = default;
};

class FinanceOperationNoMoneyException : public FinanceException {
 public:
  explicit FinanceOperationNoMoneyException(const char* arg)
      : FinanceException(arg){};
  virtual ~FinanceOperationNoMoneyException() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_FINANCE_EXCEPTION_H_