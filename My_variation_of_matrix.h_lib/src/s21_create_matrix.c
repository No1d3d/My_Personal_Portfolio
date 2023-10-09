#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int CODE = OK;
  if (result != NULL && rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  } else {
    CODE = INCORRECT_MATRIX;
  }
  return CODE;
}

int s21_check_matrix(matrix_t *A) {
  return A != NULL && A->matrix != NULL && (A->columns > 0 && A->rows > 0);
}