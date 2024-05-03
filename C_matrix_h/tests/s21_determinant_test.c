#include "unit.h"

START_TEST(determinant_1) {
  matrix_t A = {0};
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  double result = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j;
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A = {0};
  int rows = 10, columns = 7;
  s21_create_matrix(rows, columns, &A);
  double result = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A = {0};
  A.matrix = NULL;
  double result = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &result), 1);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t A = {0};
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  double result = 0.0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  s21_determinant(&A, &result);
  ck_assert_double_eq(result, -5);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t A;
  double result = 0;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j * 4.5;
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq(result, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_7) {
  matrix_t A;
  double result = 0;
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  double vars[9] = {1, 2, 3, 4, 5, 7, 7, 8, 9};
  int k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = vars[k++];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &result), 0);
  ck_assert_double_eq(result, 6);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_determinant(void) {
  Suite *s = suite_create("determinant");
  TCase *tc_determinant = tcase_create("determinant");
  suite_add_tcase(s, tc_determinant);

  tcase_add_test(tc_determinant, determinant_1);
  tcase_add_test(tc_determinant, determinant_3);
  tcase_add_test(tc_determinant, determinant_4);
  tcase_add_test(tc_determinant, determinant_5);
  tcase_add_test(tc_determinant, determinant_6);
  tcase_add_test(tc_determinant, determinant_7);
  return s;
}
