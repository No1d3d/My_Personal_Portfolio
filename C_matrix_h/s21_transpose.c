#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int CODE = OK;
  if (s21_check_matrix(A)) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else {
    CODE = INCORRECT_MATRIX;
  }
  return CODE;
}