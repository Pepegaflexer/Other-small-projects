#include "3d_viewer.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (check_matrix(A) && check_matrix(B)) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      if (!(error = s21_create_matrix(A->rows, A->columns, result))) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      error = INCORRECT_MATRIX;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (check_matrix(A) && check_matrix(B)) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      if (!(error = s21_create_matrix(A->rows, A->columns, result))) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      error = INCORRECT_MATRIX;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (check_matrix(A)) {
    if (!(error = s21_create_matrix(A->rows, A->columns, result))) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (check_matrix(A) && check_matrix(B) && result != NULL) {
    if (A->columns == B->rows) {
      if (!(error = s21_create_matrix(A->rows, B->columns, result))) {
        for (int i = 0; i < A->rows; i += 1) {
          for (int j = 0; j < B->columns; j += 1) {
            for (int n = 0; n < B->rows; n += 1) {
              result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
            }
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
