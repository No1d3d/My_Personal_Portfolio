#ifndef S21_SMART_CALC_V20_CONTROLLER_CREDIT_CONTROLLER_H_
#define S21_SMART_CALC_V20_CONTROLLER_CREDIT_CONTROLLER_H_

#include "../interfaces/credit_controller_interface.h"
#include "../interfaces/credit_model_interface.h"

namespace s21 {

class CreditController final : public CreditControllerInterface {
 public:
  CreditController() = delete;
  explicit CreditController(CreditModelInterface* model);
  CreditController(const CreditController& other) = delete;
  CreditController(CreditController&& other) = delete;
  CreditController& operator=(const CreditController& other) = delete;
  CreditController& operator=(CreditController&& other) = delete;
  ~CreditController() = default;

  void SetCreditSum(double sum) override;
  void SetCreditMonths(int months) override;
  void SetCreditInterest(double interest) override;
  void SetCreditType(int type) override;
  void CalculateCredit() override;

 private:
  CreditModelInterface* model_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_CONTROLLER_CREDIT_CONTROLLER_H_