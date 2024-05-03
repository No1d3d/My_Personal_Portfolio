#ifndef S21_SMART_CALC_V20_MODELS_CALC_MODEL_FACADE_H_
#define S21_SMART_CALC_V20_MODELS_CALC_MODEL_FACADE_H_

#include "helpers/notifier.h"
#include "interfaces/credit_model_interface.h"
#include "interfaces/deposit_model_interface.h"
#include "interfaces/graph_model_interface.h"
#include "interfaces/math_model_interface.h"
#include "models/credit/credit_model.h"
#include "models/deposit/deposit_model.h"
#include "models/graph/graph_model.h"
#include "models/math/math_model.h"

namespace s21 {

class CalcModelFacade final : public MathModelInterface,
                              public GraphModelInterface,
                              public CreditModelInterface,
                              public DepositModelInterface {
 public:
  CalcModelFacade();
  CalcModelFacade(const CalcModelFacade& other) = delete;
  CalcModelFacade(CalcModelFacade&& other) = delete;
  CalcModelFacade& operator=(const CalcModelFacade& other) = delete;
  CalcModelFacade& operator=(CalcModelFacade&& other) = delete;
  ~CalcModelFacade();

  void SetMathExpression(const std::string& new_expression) override;
  void SetXValue(double x_value) override;
  void MathExpressionAddString(const char* add) override;
  void MathExpressionEraseEnd() override;
  double GetMathResult() override;
  double GetXValue() override;
  std::string GetMathExpression() override;
  bool IsMathCalculated() override;
  void CalculateX() override;
  void RegisterObserver(MathObserverUpdateInterface* object) override;
  void RegisterObserver(MathObserverErrorInterface* object) override;
  void RemoveObserver(MathObserverUpdateInterface* object) override;
  void RemoveObserver(MathObserverErrorInterface* object) override;

  void SetGraphExpression(const std::string& new_expression) override;
  void SetGraphBeginX(double new_x) override;
  void SetGraphEndX(double new_x) override;
  void SetGraphBeginY(double new_y) override;
  void SetGraphEndY(double new_y) override;
  void SetGraphYScaleAuto(bool flag) override;
  double GetGraphXBegin() override;
  double GetGraphXEnd() override;
  double GetGraphYBegin() override;
  double GetGraphYEnd() override;
  bool GetGraphYScaleAuto() override;
  const std::vector<std::pair<double, double>>& GetGraphPoints() override;
  void CalculateGraph() override;
  void RegisterObserver(GraphObserverUpdateInterface* object) override;
  void RegisterObserver(GraphObserverErrorInterface* object) override;
  void RemoveObserver(GraphObserverUpdateInterface* object) override;
  void RemoveObserver(GraphObserverErrorInterface* object) override;

  void SetCreditSum(double sum) override;
  void SetCreditMonths(int months) override;
  void SetCreditInterest(double interest) override;
  void SetCreditType(IPaymentsCreditTypes type) override;
  double GetCreditPaymentMin() override;
  double GetCreditPaymentMax() override;
  double GetCreditOverpayment() override;
  double GetCreditTotal() override;
  double GetCreditSum() override;
  int GetCreditMonths() override;
  double GetCreditInterest() override;
  IPaymentsCreditTypes GetCreditPaymentsType() override;
  bool IsCreditCalculated() override;
  void CalculateCredit() override;
  void RegisterObserver(CreditObserverUpdateInterface* object) override;
  void RegisterObserver(CreditObserverErrorInterface* object) override;
  void RemoveObserver(CreditObserverUpdateInterface* object) override;
  void RemoveObserver(CreditObserverErrorInterface* object) override;

  void SetDepositSum(double sum) override;
  void SetDepositPeriod(int months) override;
  void SetDepositInterest(double interest) override;
  void SetDepositTax(double tax) override;
  void SetDepositPeriodicityType(
      IPaymentsPeriodicityDepositTypes type) override;
  void SetDepositCapitalization(bool capitalization) override;
  void SetDepositDateStart(int year, int month, int day) override;

  void AddDepositOperationReplenishment(int year, int month, int day,
                                        double amount) override;
  void AddDepositOperationWithdrawal(int year, int month, int day,
                                     double amount) override;

  double GetDepositInterestPayment() override;
  double GetDepositTotalPayment() override;
  double GetDepositTaxPayment() override;
  bool IsDepositCalculated() override;
  double GetDepositSum() override;
  int GetDepositMonths() override;
  double GetDepositInterest() override;
  double GetDepositTax() override;
  IPaymentsPeriodicityDepositTypes GetDepositPaymentsPeriodicity() override;
  bool GetDepositCapitalizationType() override;
  void ClearDepositOperationsList() override;
  void CalculateDeposit() override;
  void RegisterObserver(DepositObserverUpdateInterface* object) override;
  void RegisterObserver(DepositObserverErrorInterface* object) override;
  void RemoveObserver(DepositObserverUpdateInterface* object) override;
  void RemoveObserver(DepositObserverErrorInterface* object) override;

 private:
  MathCalcModel* math_calc_model_;
  GraphCalcModel* graph_calc_model_;
  CreditCalcModel* credit_calc_model_;
  DepositCalcModel* deposit_calc_model_;

  Notifier math_notifier_;
  Notifier graph_notifier_;
  Notifier credit_notifier_;
  Notifier deposit_notifier_;

  void MathExceptionHandle();
  void GraphExceptionHandle();
  void CreditExceptionHandle();
  void DepositExceptionHandle();

  void NotifyUpdateMathObservers();
  void NotifyErrorMathObservers(
      const std::pair<std::string, std::string>& error);
  void NotifyUpdateGraphObservers();
  void NotifyErrorGraphObservers(
      const std::pair<std::string, std::string>& error);
  void NotifyUpdateCreditObservers();
  void NotifyErrorCreditObservers(
      const std::pair<std::string, std::string>& error);
  void NotifyUpdateDepositObservers();
  void NotifyErrorDepositObservers(
      const std::pair<std::string, std::string>& error);
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_CALC_MODEL_FACADE_H_