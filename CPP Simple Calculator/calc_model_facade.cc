#include "calc_model_facade.h"

#include "helpers/math_helpers.h"
#include "models/calc_exception.h"
#include "models/finance_exception.h"

namespace s21 {

CalcModelFacade::CalcModelFacade()
    : math_calc_model_(new MathCalcModel),
      graph_calc_model_(new GraphCalcModel),
      credit_calc_model_(new CreditCalcModel),
      deposit_calc_model_(new DepositCalcModel) {}

CalcModelFacade::~CalcModelFacade() {
  delete math_calc_model_;
  delete graph_calc_model_;
  delete credit_calc_model_;
  delete deposit_calc_model_;
}

void CalcModelFacade::SetMathExpression(const std::string &new_expression) {
  math_calc_model_->set_math_expression(new_expression);
}

void CalcModelFacade::SetXValue(double x_value) {
  math_calc_model_->set_x_value(x_value);
}

void CalcModelFacade::MathExpressionAddString(const char *add) {
  try {
    math_calc_model_->MathExpressionAddString(add);
    NotifyUpdateMathObservers();
  } catch (const S21CalcException &) {
    MathExceptionHandle();
  }
}

void CalcModelFacade::MathExpressionEraseEnd() {
  math_calc_model_->MathExpressionEraseEnd();
  NotifyUpdateMathObservers();
}

double CalcModelFacade::GetMathResult() {
  return math_calc_model_->get_result();
}

double CalcModelFacade::GetXValue() { return math_calc_model_->get_x_value(); }

std::string CalcModelFacade::GetMathExpression() {
  return math_calc_model_->get_math_expression();
}

bool CalcModelFacade::IsMathCalculated() {
  return math_calc_model_->get_is_calculated();
}

void CalcModelFacade::CalculateX() {
  try {
    math_calc_model_->Calculate();
    NotifyUpdateMathObservers();
  } catch (const S21CalcException &) {
    MathExceptionHandle();
  }
}

void CalcModelFacade::RegisterObserver(MathObserverUpdateInterface *object) {
  math_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RegisterObserver(MathObserverErrorInterface *object) {
  math_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RemoveObserver(MathObserverUpdateInterface *object) {
  math_notifier_.RemoveObserver(object);
}

void CalcModelFacade::RemoveObserver(MathObserverErrorInterface *object) {
  math_notifier_.RemoveObserver(object);
}

void CalcModelFacade::SetGraphExpression(const std::string &new_expression) {
  graph_calc_model_->set_math_expression(new_expression);
}

void CalcModelFacade::SetGraphBeginX(double new_x) {
  graph_calc_model_->set_x_begin(new_x);
}

void CalcModelFacade::SetGraphEndX(double new_x) {
  graph_calc_model_->set_x_end(new_x);
}

void CalcModelFacade::SetGraphBeginY(double new_y) {
  graph_calc_model_->set_y_begin(new_y);
}

void CalcModelFacade::SetGraphYScaleAuto(bool flag) {
  graph_calc_model_->set_y_scale_auto(flag);
}

void CalcModelFacade::SetGraphEndY(double new_y) {
  graph_calc_model_->set_y_end(new_y);
}

double CalcModelFacade::GetGraphXBegin() {
  return graph_calc_model_->get_x_begin();
}

double CalcModelFacade::GetGraphXEnd() {
  return graph_calc_model_->get_x_end();
}

double CalcModelFacade::GetGraphYBegin() {
  return graph_calc_model_->get_y_begin();
}

double CalcModelFacade::GetGraphYEnd() {
  return graph_calc_model_->get_y_end();
}

bool CalcModelFacade::GetGraphYScaleAuto() {
  return graph_calc_model_->get_y_scale_auto();
}

const std::vector<std::pair<double, double>>
    &CalcModelFacade::GetGraphPoints() {
  return graph_calc_model_->get_points();
}

void CalcModelFacade::CalculateGraph() {
  try {
    graph_calc_model_->CalculateGraph();
    NotifyUpdateGraphObservers();
  } catch (const S21CalcException &) {
    GraphExceptionHandle();
  }
}

void CalcModelFacade::RegisterObserver(GraphObserverUpdateInterface *object) {
  graph_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RegisterObserver(GraphObserverErrorInterface *object) {
  graph_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RemoveObserver(GraphObserverUpdateInterface *object) {
  graph_notifier_.RemoveObserver(object);
}

void CalcModelFacade::RemoveObserver(GraphObserverErrorInterface *object) {
  graph_notifier_.RemoveObserver(object);
}

void CalcModelFacade::SetCreditSum(double sum) {
  credit_calc_model_->set_sum(sum);
}

void CalcModelFacade::SetCreditMonths(int months) {
  credit_calc_model_->set_months(months);
}

void CalcModelFacade::SetCreditInterest(double interest) {
  credit_calc_model_->set_interest(interest);
}

void CalcModelFacade::SetCreditType(IPaymentsCreditTypes type) {
  if (type == kPaymentsAnnuity) {
    credit_calc_model_->set_type(CreditCalcModel::kPaymentsAnnuity);
  } else {
    credit_calc_model_->set_type(CreditCalcModel::kPaymentsDifferentiated);
  }
}

double CalcModelFacade::GetCreditPaymentMin() {
  return credit_calc_model_->get_payment_min();
}
double CalcModelFacade::GetCreditPaymentMax() {
  return credit_calc_model_->get_payment_max();
}
double CalcModelFacade::GetCreditOverpayment() {
  return credit_calc_model_->get_overpayment();
}
double CalcModelFacade::GetCreditTotal() {
  return credit_calc_model_->get_payment_total();
}

double CalcModelFacade::GetCreditSum() { return credit_calc_model_->get_sum(); }

int CalcModelFacade::GetCreditMonths() {
  return credit_calc_model_->get_months();
}

double CalcModelFacade::GetCreditInterest() {
  return credit_calc_model_->get_interest();
}

IPaymentsCreditTypes CalcModelFacade::GetCreditPaymentsType() {
  CreditCalcModel::PaymentsCreditTypes result = credit_calc_model_->get_type();
  if (result == CreditCalcModel::kPaymentsAnnuity) {
    return kPaymentsAnnuity;
  } else {
    return kPaymentsDifferentiated;
  }
}

bool CalcModelFacade::IsCreditCalculated() {
  return credit_calc_model_->get_is_calculated();
}

void CalcModelFacade::CalculateCredit() {
  try {
    credit_calc_model_->CalculateCredit();
    NotifyUpdateCreditObservers();
  } catch (const FinanceException &) {
    CreditExceptionHandle();
  }
}

void CalcModelFacade::RegisterObserver(CreditObserverUpdateInterface *object) {
  credit_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RegisterObserver(CreditObserverErrorInterface *object) {
  credit_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RemoveObserver(CreditObserverUpdateInterface *object) {
  credit_notifier_.RemoveObserver(object);
}

void CalcModelFacade::RemoveObserver(CreditObserverErrorInterface *object) {
  credit_notifier_.RemoveObserver(object);
}

void CalcModelFacade::SetDepositSum(double sum) {
  deposit_calc_model_->set_sum(sum);
}

void CalcModelFacade::SetDepositPeriod(int months) {
  deposit_calc_model_->set_months(months);
}

void CalcModelFacade::SetDepositInterest(double interest) {
  deposit_calc_model_->set_interest(interest);
}

void CalcModelFacade::SetDepositTax(double tax) {
  deposit_calc_model_->set_tax(tax);
}

void CalcModelFacade::SetDepositPeriodicityType(
    IPaymentsPeriodicityDepositTypes type) {
  if (type == kPaymentsDay) {
    deposit_calc_model_->set_payments_periodicity(
        DepositCalcModel::kPaymentsDay);
  } else if (type == kPaymentsEnd) {
    deposit_calc_model_->set_payments_periodicity(
        DepositCalcModel::kPaymentsEnd);
  } else {
    deposit_calc_model_->set_payments_periodicity(
        DepositCalcModel::kPaymentsMonth);
  }
}

void CalcModelFacade::SetDepositCapitalization(bool capitalization) {
  deposit_calc_model_->set_capitalization(capitalization);
}

void CalcModelFacade::SetDepositDateStart(int year, int month, int day) {
  deposit_calc_model_->set_date_start(year, month, day);
}

void CalcModelFacade::AddDepositOperationReplenishment(int year, int month,
                                                       int day, double amount) {
  deposit_calc_model_->AddOperation(year, month, day, amount);
}

void CalcModelFacade::AddDepositOperationWithdrawal(int year, int month,
                                                    int day, double amount) {
  deposit_calc_model_->AddOperation(year, month, day, -amount);
}

double CalcModelFacade::GetDepositInterestPayment() {
  return deposit_calc_model_->get_interest_amount();
}

double CalcModelFacade::GetDepositTotalPayment() {
  return deposit_calc_model_->get_deposit_amount();
}

double CalcModelFacade::GetDepositTaxPayment() {
  return deposit_calc_model_->get_tax_amount();
}

bool CalcModelFacade::IsDepositCalculated() {
  return deposit_calc_model_->get_is_calculated();
}

double CalcModelFacade::GetDepositSum() {
  return deposit_calc_model_->get_sum();
}

int CalcModelFacade::GetDepositMonths() {
  return deposit_calc_model_->get_months();
}

double CalcModelFacade::GetDepositInterest() {
  return deposit_calc_model_->get_interest();
}

double CalcModelFacade::GetDepositTax() {
  return deposit_calc_model_->get_tax();
}

IPaymentsPeriodicityDepositTypes
CalcModelFacade::GetDepositPaymentsPeriodicity() {
  DepositCalcModel::PaymentsPeriodicityDepositTypes type =
      deposit_calc_model_->get_payments_periodicity();

  if (type == DepositCalcModel::kPaymentsDay) {
    return kPaymentsDay;
  } else if (type == DepositCalcModel::kPaymentsEnd) {
    return kPaymentsEnd;
  } else {
    return kPaymentsMonth;
  }
}

bool CalcModelFacade::GetDepositCapitalizationType() {
  return deposit_calc_model_->get_capitalization_type();
}

void CalcModelFacade::ClearDepositOperationsList() {
  deposit_calc_model_->ClearOperationsList();
}

void CalcModelFacade::CalculateDeposit() {
  try {
    deposit_calc_model_->CalculateDeposit();
    NotifyUpdateDepositObservers();
  } catch (const FinanceException &) {
    DepositExceptionHandle();
  }
}

void CalcModelFacade::RegisterObserver(DepositObserverUpdateInterface *object) {
  deposit_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RegisterObserver(DepositObserverErrorInterface *object) {
  deposit_notifier_.RegisterObserver(object);
}

void CalcModelFacade::RemoveObserver(DepositObserverUpdateInterface *object) {
  deposit_notifier_.RemoveObserver(object);
}

void CalcModelFacade::RemoveObserver(DepositObserverErrorInterface *object) {
  deposit_notifier_.RemoveObserver(object);
}

void CalcModelFacade::MathExceptionHandle() {
  try {
    throw;
  } catch (const S21InputZeroLengthException &) {
    NotifyErrorMathObservers(
        {"input", "Mathematical expression should be entered!"});
  } catch (const S21InputTooLongException &) {
    NotifyErrorMathObservers(
        {"input", "Mathematical expression should be shorter than " +
                      math_helpers::HumanFormat(
                          static_cast<int>(MathCalcModel::kMaxInputSize))});
  } catch (const S21InputIncorrectException &) {
    NotifyErrorMathObservers({"input", "Incorrect mathematical expression!"});
  } catch (const S21WrongOperatorException &) {
    NotifyErrorMathObservers(
        {"wrong_operator", "Use of prohibibted operator!"});
  } catch (const S21CalcException &) {
    NotifyErrorMathObservers({"other", "Unexpected error!"});
  }
}

void CalcModelFacade::GraphExceptionHandle() {
  try {
    throw;
  } catch (const S21WrongXGraphException &) {
    NotifyErrorGraphObservers(
        {"x_graph", "X values should be in range from " +
                        math_helpers::HumanFormat(graph_calc_model_->kMinX) +
                        " to " +
                        math_helpers::HumanFormat(graph_calc_model_->kMaxX)});
  } catch (const S21WrongYGraphException &) {
    NotifyErrorGraphObservers(
        {"y_graph", "Y values should be in range from " +
                        math_helpers::HumanFormat(graph_calc_model_->kMinY) +
                        " to " +
                        math_helpers::HumanFormat(graph_calc_model_->kMaxY)});
  } catch (const S21InputZeroLengthException &) {
    NotifyErrorGraphObservers(
        {"graph_calculation",
         "Graph points calc. error - Mathematical expression "
         "be entered!"});
  } catch (const S21InputTooLongException &) {
    NotifyErrorGraphObservers(
        {"graph_calculation",
         "Graph points calc. error  - Mathematical expression "
         "should be shorter than " +
             math_helpers::HumanFormat(
                 static_cast<int>(MathCalcModel::kMaxInputSize))});
  } catch (const S21InputIncorrectException &) {
    NotifyErrorGraphObservers({"graph_calculation",
                               "Graph points calc. error  - "
                               "Incorrect mathematical expression!"});
  } catch (const S21CalcException &) {
    NotifyErrorGraphObservers({"other", "Неизвестная ошибка"});
  }
}

void CalcModelFacade::CreditExceptionHandle() {
  try {
    throw;
  } catch (const FinanceSumException &) {
    NotifyErrorCreditObservers(
        {"sum",
         "Credit value should be in range from " +
             math_helpers::HumanFormat(credit_calc_model_->kMinCreditSum) +
             " to " +
             math_helpers::HumanFormat(credit_calc_model_->kMaxCreditSum) +
             " (rub.)"});
  } catch (const FinanceMonthException &) {
    NotifyErrorCreditObservers(
        {"months",
         "Сredit term should be from " +
             math_helpers::HumanFormat(credit_calc_model_->kMinCreditMonths) +
             " to " +
             math_helpers::HumanFormat(credit_calc_model_->kMaxCreditMonths) +
             " (mon.)"});
  } catch (const FinanceInterestException &) {
    NotifyErrorCreditObservers(
        {"interest",
         "Credit rate should be from " +
             math_helpers::HumanFormat(credit_calc_model_->kMinCreditInterest) +
             " to " +
             math_helpers::HumanFormat(credit_calc_model_->kMaxCreditInterest) +
             " (%)"});
  } catch (const FinanceException &) {
    NotifyErrorCreditObservers({"other", "Unexpected error"});
  }
}

void CalcModelFacade::DepositExceptionHandle() {
  try {
    throw;
  } catch (const FinanceSumException &) {
    NotifyErrorDepositObservers(
        {"sum",
         "Deposit sum should be from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositSum) +
             " to " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositSum) +
             " (rub.)"});
  } catch (const FinanceMonthException &) {
    NotifyErrorDepositObservers(
        {"months",
         "Deposit term should be from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositMonths) +
             " to " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositMonths) +
             " (mon.)"});
  } catch (const FinanceInterestException &) {
    NotifyErrorDepositObservers(
        {"interest", "Deposit rate should be from " +
                         math_helpers::HumanFormat(
                             deposit_calc_model_->kMinDepositInterest) +
                         " to " +
                         math_helpers::HumanFormat(
                             deposit_calc_model_->kMaxDepositInterest) +
                         " (%)"});

  } catch (const FinanceTaxException &) {
    NotifyErrorDepositObservers(
        {"tax",
         "Tax rate should be in range from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositTax) +
             " to " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositTax) +
             " (%)"});
  } catch (const FinanceDateStartException &) {
    NotifyErrorDepositObservers(
        {"date_start",
         "Incorrect deposit date (should be in range from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositYear) +
             " and " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositYear) +
             " years)"});
  } catch (const FinanceDateOperationPlusException &) {
    NotifyErrorDepositObservers(
        {"replenishment_date",
         "Incorrect replenishment date (should be in range from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositYear) +
             " and " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositYear) +
             " years)"});
  } catch (const FinanceDateOperationMinusException &) {
    NotifyErrorDepositObservers(
        {"withdrawal_date",
         "Incorrect withdrawal date (should be in range from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositYear) +
             " till " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositYear) +
             " years)"});
  } catch (const FinanceSumOperationPlusException &) {
    NotifyErrorDepositObservers(
        {"replenishment_sum",
         "Replenishment sum should be from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositSum) +
             " to " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositSum) +
             " (rub.)"});
  } catch (const FinanceSumOperationMinusException &) {
    NotifyErrorDepositObservers(
        {"withdrawal_sum",
         "Withdrawal sum should be from " +
             math_helpers::HumanFormat(deposit_calc_model_->kMinDepositSum) +
             " to " +
             math_helpers::HumanFormat(deposit_calc_model_->kMaxDepositSum) +
             " (rub.)"});
  } catch (const FinanceOperationNoMoneyException &) {
    NotifyErrorDepositObservers(
        {"operations_no_money", "Not enogh money on account for operation!"});
  } catch (const FinanceException &) {
    NotifyErrorDepositObservers({"other", "Unexpected error!"});
  }
}

void CalcModelFacade::NotifyUpdateMathObservers() {
  math_notifier_.NotifyUpdateObservers();
}

void CalcModelFacade::NotifyErrorMathObservers(
    const std::pair<std::string, std::string> &error) {
  math_notifier_.NotifyErrorObservers(error);
}

void CalcModelFacade::NotifyUpdateGraphObservers() {
  graph_notifier_.NotifyUpdateObservers();
}

void CalcModelFacade::NotifyErrorGraphObservers(
    const std::pair<std::string, std::string> &error) {
  graph_notifier_.NotifyErrorObservers(error);
}

void CalcModelFacade::NotifyUpdateCreditObservers() {
  credit_notifier_.NotifyUpdateObservers();
}

void CalcModelFacade::NotifyErrorCreditObservers(
    const std::pair<std::string, std::string> &error) {
  credit_notifier_.NotifyErrorObservers(error);
}

void CalcModelFacade::NotifyUpdateDepositObservers() {
  deposit_notifier_.NotifyUpdateObservers();
}

void CalcModelFacade::NotifyErrorDepositObservers(
    const std::pair<std::string, std::string> &error) {
  deposit_notifier_.NotifyErrorObservers(error);
}

}  // namespace s21
