#ifndef S21_SMART_CALC_V20_CONTROLLER_DEPOSIT_CONTROLLER_H_
#define S21_SMART_CALC_V20_CONTROLLER_DEPOSIT_CONTROLLER_H_

#include "../interfaces/deposit_controller_interface.h"
#include "../interfaces/deposit_model_interface.h"

namespace s21 {

class DepositController final : public DepositControllerInterface {
 public:
  DepositController() = delete;
  explicit DepositController(DepositModelInterface* model);
  DepositController(const DepositController& other) = delete;
  DepositController(DepositController&& other) = delete;
  DepositController& operator=(const DepositController& other) = delete;
  DepositController& operator=(DepositController&& other) = delete;
  ~DepositController() = default;

  void SetDepositSum(double sum) override;
  void SetDepositPeriod(int months) override;
  void SetDepositInterest(double interest) override;
  void SetDepositTax(double tax) override;
  void SetDepositPeriodicityType(int type) override;
  void SetDepositCapitalization(bool capitalization) override;
  void SetDepositDateStart(int year, int month, int day) override;
  void AddDepositOperationReplenishment(int year, int month, int day,
                                        double amount) override;
  void AddDepositOperationWithdrawal(int year, int month, int day,
                                     double amount) override;
  void ClearDepositOperationsList() override;
  void CalculateDeposit() override;

 private:
  DepositModelInterface* model_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_CONTROLLER_DEPOSIT_CONTROLLER_H_