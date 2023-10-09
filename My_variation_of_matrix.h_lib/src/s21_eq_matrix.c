#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int CODE = SUCCESS;
  if (s21_check_matrix(A) && s21_check_matrix(B) && A->columns == B->columns &&
      A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs((A->matrix)[i][j] - (B->matrix)[i][j]) > 1e-7) {
          CODE = FAILURE;
          break;
        }
      }
      if (CODE == FAILURE) break;
    }
  } else {
    CODE = FAILURE;
  }
  return CODE;
}