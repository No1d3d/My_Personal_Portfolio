#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int CODE = OK;
  if (A == NULL || !s21_check_matrix(A)) {
    CODE = INCORRECT_MATRIX;
  } else if (A->rows != A->columns || determinant(A->matrix, A->rows) == 0) {
    CODE = CALCULATION_ERROR;
  } else {
    s21_calc_complements(A, result);
    matrix_t tmp = {0};
    s21_transpose(result, &tmp);
    s21_remove_matrix(result);
    double det = 0;
    s21_determinant(A, &det);
    s21_mult_number(&tmp, tmp.rows == 1 ? pow(det, -2) : (1.0 / det), result);
    s21_remove_matrix(&tmp);
  }
  return CODE;
}