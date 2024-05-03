#ifndef S21_SMART_CALC_V20_MODELS_CALC_EXCEPTION_H_
#define S21_SMART_CALC_V20_MODELS_CALC_EXCEPTION_H_

#include <stdexcept>

namespace s21 {

class S21CalcException : public std::runtime_error {
 public:
  explicit S21CalcException(const char* arg) : runtime_error(arg){};
  virtual ~S21CalcException() = default;
};

class S21InputZeroLengthException : public S21CalcException {
 public:
  explicit S21InputZeroLengthException(const char* arg)
      : S21CalcException(arg){};
  virtual ~S21InputZeroLengthException() = default;
};

class S21InputTooLongException : public S21CalcException {
 public:
  explicit S21InputTooLongException(const char* arg) : S21CalcException(arg){};
  virtual ~S21InputTooLongException() = default;
};

class S21InputIncorrectException : public S21CalcException {
 public:
  explicit S21InputIncorrectException(const char* arg)
      : S21CalcException(arg){};
  virtual ~S21InputIncorrectException() = default;
};

class S21WrongOperatorException : public S21CalcException {
 public:
  explicit S21WrongOperatorException(const char* arg) : S21CalcException(arg){};
  virtual ~S21WrongOperatorException() = default;
};

class S21WrongXGraphException : public S21CalcException {
 public:
  explicit S21WrongXGraphException(const char* arg) : S21CalcException(arg){};
  virtual ~S21WrongXGraphException() = default;
};

class S21WrongYGraphException : public S21CalcException {
 public:
  explicit S21WrongYGraphException(const char* arg) : S21CalcException(arg){};
  virtual ~S21WrongYGraphException() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_CALC_EXCEPTION_H_