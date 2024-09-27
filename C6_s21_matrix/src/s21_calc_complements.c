#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  matrix_t temp;
  if (check_matrix(A) && result != NULL) {
    if (A->rows == A->columns) {
      if (!(error = s21_create_matrix(A->rows, A->columns, result))) {
        if (A->rows == 1) {
          result->matrix[0][0] = 1;
        } else if (A->rows == 2) {
          calcCompForDva(A, result);
        } else {
          if (!(error =
                    s21_create_matrix(A->rows - 1, A->columns - 1, &temp))) {
            calcComp(A, result, &temp);
            s21_remove_matrix(&temp);
          }
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

void makeMinor(matrix_t *A, matrix_t *temp, int skipR, int skipC) {
  int stolb = 0, stroka = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      if ((i != skipR) && (j != skipC)) {
        temp->matrix[stroka][stolb] = A->matrix[i][j];
        stolb++;
      }
    }
    stolb = 0;
    if (i != skipR) {
      stroka++;
    }
  }
}

void calcComp(matrix_t *A, matrix_t *result, matrix_t *temp) {
  double det = 0.0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      makeMinor(A, temp, i, j);
      s21_determinant(temp, &det);
      result->matrix[i][j] = det * pow(-1, i + j);
    }
  }
}

void calcCompForDva(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] =
          A->matrix[A->rows - i - 1][A->rows - j - 1] * pow(-1, i + j);
    }
  }
}