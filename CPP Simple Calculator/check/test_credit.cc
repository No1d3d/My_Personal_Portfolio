#include <gtest/gtest.h>

#include <limits>

#include "../models/credit/credit_model.h"
#include "../models/finance_exception.h"

namespace {

const double kCalcEpsilon = 1e-2;

TEST(TestCreditCalcModel, TestCalculateCreditFail1) {
  s21::CreditCalcModel credit_model;

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail2) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(200000);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceMonthException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail3) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(200000);
  credit_model.set_months(24);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail4) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(0);
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail5) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(10000000000);
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail6) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(std::numeric_limits<double>::infinity());
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail7) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(std::numeric_limits<double>::quiet_NaN());
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail8) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(-1000);
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceSumException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail9) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(0);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceMonthException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail10) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(-1);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceMonthException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail11) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(50 * 12 + 1);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceMonthException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail12) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(24);
  credit_model.set_interest(0);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail13) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(24);
  credit_model.set_interest(-1);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail14) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(24);
  credit_model.set_interest(1000);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail15) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(24);
  credit_model.set_interest(std::numeric_limits<double>::infinity());
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditFail16) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000);
  credit_model.set_months(24);
  credit_model.set_interest(std::numeric_limits<double>::quiet_NaN());
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  EXPECT_THROW(credit_model.CalculateCredit(), s21::FinanceInterestException);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk1) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(200000);
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 9414.69, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 9414.69, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 25952.56, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 225952.56, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk2) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(200000);
  credit_model.set_months(24);
  credit_model.set_interest(12);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 8416.67, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 10333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 25000.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 225000.00, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk3) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(9578.75);
  credit_model.set_months(3);
  credit_model.set_interest(11.12345);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 3252.29, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 3252.29, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 178.12, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 9756.87, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk4) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(9578.75);
  credit_model.set_months(3);
  credit_model.set_interest(11.12345);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 3222.51, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 3281.71, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 177.58, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 9756.33, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk5) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(9999999999.99);
  credit_model.set_months(50 * 12);
  credit_model.set_interest(999);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 8324999999.99, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 8324999999.99, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 4984999999994.01, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 4994999999994.00, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk6) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(9999999999.99);
  credit_model.set_months(50 * 12);
  credit_model.set_interest(999);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 30541666.67, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 8341666666.66, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 2501662499997.19, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 2511662499997.18, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk7) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1);
  credit_model.set_months(1);
  credit_model.set_interest(0.5);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 0, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 1, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk8) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1);
  credit_model.set_months(1);
  credit_model.set_interest(0.5);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 0, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 1, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk9) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(12345.99);
  credit_model.set_months(12);
  credit_model.set_interest(15);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1114.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1114.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 1025.97, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 13371.96, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk10) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(12345.99);
  credit_model.set_months(12);
  credit_model.set_interest(15);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1041.69, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1183.16, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 1003.11, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 13349.10, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk11) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000000);
  credit_model.set_months(50 * 12);
  credit_model.set_interest(0.01);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1670.84, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1670.84, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 2504.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 1002504.00, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk12) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(1000000);
  credit_model.set_months(50 * 12);
  credit_model.set_interest(0.01);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 1666.68, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 1675.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 2504.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 1002504.33, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk13) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(100500);
  credit_model.set_months(2 * 12);
  credit_model.set_interest(6);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 4454.22, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 4454.22, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 6401.28, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 106901.28, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk14) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(100500);
  credit_model.set_months(2 * 12);
  credit_model.set_interest(6);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 4208.44, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 4690.00, kCalcEpsilon);

  EXPECT_NEAR(credit_model.get_overpayment(), 6281.28, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 106781.28, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk15) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(0.01);
  credit_model.set_months(49 * 12);
  credit_model.set_interest(111);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 0.0, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 0.0, kCalcEpsilon);
  // Каким бы странным не был этот тест, но он совпадает с calcus.ru :)
  EXPECT_NEAR(credit_model.get_overpayment(), -0.01, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 0.0, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk16) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(100000);
  credit_model.set_months(2);
  credit_model.set_interest(100);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 54166.67, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 58333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 12500.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 112500.00, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk17) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(100000);
  credit_model.set_months(1);
  credit_model.set_interest(100);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsAnnuity);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 108333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 108333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 8333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 108333.33, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk18) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(10000000);
  credit_model.set_months(1);
  credit_model.set_interest(999);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 18325000.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 18325000.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 8325000.00, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 18325000.00, kCalcEpsilon);
}

TEST(TestCreditCalcModel, TestCalculateCreditOk19) {
  s21::CreditCalcModel credit_model;
  credit_model.set_sum(100000);
  credit_model.set_months(1);
  credit_model.set_interest(100);
  credit_model.set_type(s21::CreditCalcModel::kPaymentsDifferentiated);

  credit_model.CalculateCredit();

  EXPECT_NEAR(credit_model.get_payment_min(), 108333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_max(), 108333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_overpayment(), 8333.33, kCalcEpsilon);
  EXPECT_NEAR(credit_model.get_payment_total(), 108333.33, kCalcEpsilon);
}

}  // namespace
