#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int CODE = 0;
  if (!s21_check_matrix(A)) {
    CODE = INCORRECT_MATRIX;
  } else if ((A->rows != A->columns)) {
    CODE = CALCULATION_ERROR;
  } else {
    *result = determinant(A->matrix, A->rows);
  }
  return CODE;
}

double determinant(double **a, int n) {
  if (n == 1) {
    return a[0][0];
  }
  double det = 0;
  for (int j = 0; j < n; j++) {
    double **minor = (double **)calloc((n - 1), sizeof(double *));
    for (int i = 0; i < n - 1; i++) {
      minor[i] = (double *)calloc((n - 1), sizeof(double));
    }
    for (int i = 1; i < n; i++) {
      for (int k = 0; k < j; k++) {
        minor[i - 1][k] = a[i][k];
      }
      for (int k = j + 1; k < n; k++) {
        minor[i - 1][k - 1] = a[i][k];
      }
    }
    double sign = (j % 2 == 0) ? 1 : -1;
    det += a[0][j] * sign * determinant(minor, n - 1);
    for (int i = 0; i < n - 1; i++) {
      free(minor[i]);
    }
    free(minor);
  }
  return det;
}
