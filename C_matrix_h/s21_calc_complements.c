#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int CODE = OK;
  if (!s21_check_matrix(A)) {
    CODE = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    CODE = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      matrixMinor(A->matrix, A->rows, result);
    }
  }
  return CODE;
}

void matrixMinor(double **a, int n, matrix_t *result) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double **minor = (double **)malloc((n - 1) * sizeof(double *));
      for (int k = 0; k < n - 1; k++) {
        minor[k] = (double *)malloc((n - 1) * sizeof(double));
      }
      int x = 0;
      for (int k = 0; k < n; k++) {
        if (k == i) {
          continue;
        }
        int y = 0;
        for (int l = 0; l < n; l++) {
          if (l == j) {
            continue;
          }
          minor[x][y] = a[k][l];
          y++;
        }
        x++;
      }
      int sign = ((i + j) % 2 == 0 ? 1 : -1);
      result->matrix[i][j] = sign * determinant(minor, n - 1);
      for (int k = 0; k < n - 1; k++) {
        free(minor[k]);
      }
      free(minor);
    }
  }
}