#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  double sign = 1;
  matrix_t temp = {0};
  if (check_matrix(A) && result != NULL) {
    if (A->rows == A->columns) {
      *result = 1.;
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        detForDva(A, result);
      } else {
        if (!(error = s21_create_matrix(A->rows, A->columns, &temp))) {
          transferMatrix(&temp, A);
          calcDet(&temp, result, &sign);
          s21_remove_matrix(&temp);
        }
      }
      if (result != 0) {
        *result *= sign;
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

void change_rows(matrix_t *A, int x, int b) {
  for (int i = 0; i < A->columns; i++) {
    double temp = A->matrix[x][i];
    A->matrix[x][i] = A->matrix[b][i];
    A->matrix[b][i] = temp;
  }
}

void detForDva(matrix_t *A, double *result) {
  *result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
}

void calcDet(matrix_t *A, double *result, double *sign) {
  for (int count = 0; count < A->rows; count++) {
    if (A->matrix[count][count] == 0) {
      int temp = -1;
      int x = count;
      int yslovie = 1;
      while (yslovie) {
        if (A->matrix[x][count] != 0) {
          temp = x;
          yslovie = 0;
        }
        if (x == A->columns - 1) {
          yslovie = 0;
        }
        x++;
      }
      if (temp == -1) {
        *result = 0;
      } else {
        *sign *= -1;
        change_rows(A, count, temp);
      }
    }
    if (*result != 0) {
      for (int i = count; i < A->rows; i++) {
        if (!(A->matrix[i][count] == 0)) {
          *result *= A->matrix[i][count];
          for (int j = A->rows - 1; j >= count; j--) {
            A->matrix[i][j] = A->matrix[i][j] / A->matrix[i][count];
          }
        }
      }
      for (int i = A->rows - 1; i > count; i--) {
        if (!(A->matrix[i][count] == 0)) {
          for (int j = count; j < A->rows; j++) {
            A->matrix[i][j] = A->matrix[i][j] - A->matrix[count][j];
          }
        }
      }
    }
  }
}