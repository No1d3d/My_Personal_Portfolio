#include <gtest/gtest.h>

#include <limits>

#include "../models/deposit/deposit_model.h"
#include "../models/finance_exception.h"

namespace {

const double kCalcEpsilon = 1e-2;

TEST(TestDepositCalcModel, TestCalculateDepositFail1) {
  s21::DepositCalcModel deposit_model;

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail2) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceMonthException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail3) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail4) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(0);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail5) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(10000000000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail6) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(std::numeric_limits<double>::infinity());
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail7) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(std::numeric_limits<double>::quiet_NaN());
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail8) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(-1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceSumException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail9) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(0);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceMonthException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail10) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(-1);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceMonthException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail11) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(50 * 12 + 1);
  deposit_model.set_interest(12);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceMonthException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail12) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail13) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(-1);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail14) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(1000);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail15) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(std::numeric_limits<double>::infinity());
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail16) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(std::numeric_limits<double>::quiet_NaN());
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceInterestException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail17) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(-0.01);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceTaxException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail18) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(100.01);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceTaxException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail19) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(std::numeric_limits<double>::infinity());
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceTaxException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail20) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(std::numeric_limits<double>::quiet_NaN());
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(), s21::FinanceTaxException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail21) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);

  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail22) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 0);

  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail23) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 2, 31);

  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 2, -9);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 2, 32);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 0, 1);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 13, 1);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 4, 31);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2023, 2, 29);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);

  deposit_model.set_date_start(2024, 2, 29);
  EXPECT_NO_THROW(deposit_model.CalculateDeposit());

  deposit_model.set_date_start(20232033, 2, 29);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail24) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2101, 1, 1);

  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail25) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(1000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(1899, 1, 1);

  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateStartException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail26) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, 54000);

  deposit_model.CalculateDeposit();
  EXPECT_NO_THROW(deposit_model.CalculateDeposit());

  deposit_model.AddOperation(2024, 8, 32, 54000);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateOperationPlusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail27) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -54000);
  EXPECT_NO_THROW(deposit_model.CalculateDeposit());

  deposit_model.AddOperation(2024, 8, 32, -54000);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceDateOperationMinusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail28) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, 0);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceSumOperationPlusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail29) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, 0);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceSumOperationPlusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail30) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -0.0);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceSumOperationMinusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail31) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -10000000000);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceSumOperationMinusException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail32) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -1000000);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceOperationNoMoneyException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail33) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2023, 12, 31, -200001);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceOperationNoMoneyException);
}

TEST(TestDepositCalcModel, TestCalculateDepositFail34) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2023, 12, 31, -200001);
  deposit_model.AddOperation(2023, 12, 31, 20000);
  EXPECT_NO_THROW(deposit_model.CalculateDeposit());

  deposit_model.AddOperation(2023, 12, 31, -19999);
  EXPECT_NO_THROW(deposit_model.CalculateDeposit());

  deposit_model.AddOperation(2023, 12, 31, -1);
  EXPECT_THROW(deposit_model.CalculateDeposit(),
               s21::FinanceOperationNoMoneyException);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk1) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2021, 9, 22);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 48000.05, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk2) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(2);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 3934.43, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 393.44, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk3) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(10.5);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 48000.03, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 5040.00, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk4) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(99.99);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 15);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 8002.88, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 8002.08, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk5) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 15);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 8002.87, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk6) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsDay);
  deposit_model.set_date_start(2023, 12, 15);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 8002.42, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 200000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk7) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 8053.22, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 208053.22, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk8) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 7934.43, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 207934.43, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk9) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(4);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsDay);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 8092.57, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 208092.57, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk10) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 1, 10, 20000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 52734.41, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 220000, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2024, 2, 1, 19990);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 57322.30, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 239990, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 3, 999.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 57421.93, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 240989.99, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 4, 999.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 57521.20, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 241989.98, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2024, 1, 11, -10000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 55157.26, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 231989.98, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 3, -0.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 55157.16, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 231988.99, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk11) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 1, 10, 20000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 59258.98, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 279258.98, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2024, 2, 1, 19990);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 64387.43, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 304377.43, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 3, 999.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 64491.61, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 305481.60, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 4, 999.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 64595.46, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 306585.44, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2024, 1, 11, -10000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 61943.47, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 293933.45, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);

  deposit_model.AddOperation(2025, 3, 3, -0.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 61943.37, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 293932.36, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk12) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsDay);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 1, 1, -200000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 65.57, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 0, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk13) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsDay);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 1, 1, -200000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 82.23, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 82.23, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk14) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -54000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 39023.61, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 146000.00, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk15) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, -54000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 39023.61, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 185023.61, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk16) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(200000);
  deposit_model.set_months(24);
  deposit_model.set_interest(12);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(true);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2024, 8, 12, 54000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 56976.39, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 310976.39, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk17) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(9999999999.99);
  deposit_model.set_months(50 * 12);
  deposit_model.set_interest(999);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsEnd);
  deposit_model.set_date_start(2023, 12, 31);

  deposit_model.AddOperation(2023, 12, 30, 9999999999.99);
  deposit_model.AddOperation(2023, 12, 30, 9999999999.99);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 4994999999995.04,
              kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 9999999999.99, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk18) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(100000);
  deposit_model.set_months(12);
  deposit_model.set_interest(10);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 9, 30);

  deposit_model.AddOperation(2023, 9, 30, -100000);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 0, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 0, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

TEST(TestDepositCalcModel, TestCalculateDepositOk19) {
  s21::DepositCalcModel deposit_model;
  deposit_model.set_sum(100000);
  deposit_model.set_months(12);
  deposit_model.set_interest(10);
  deposit_model.set_tax(0);
  deposit_model.set_capitalization(false);
  deposit_model.set_payments_periodicity(s21::DepositCalcModel::kPaymentsMonth);
  deposit_model.set_date_start(2023, 9, 30);

  deposit_model.AddOperation(2023, 9, 30, 1);
  deposit_model.AddOperation(2023, 9, 30, -100000.01);
  deposit_model.CalculateDeposit();

  EXPECT_NEAR(deposit_model.get_interest_amount(), 0.12, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_deposit_amount(), 0.99, kCalcEpsilon);
  EXPECT_NEAR(deposit_model.get_tax_amount(), 0, kCalcEpsilon);
}

}  // namespace
