#include "3d_viewer.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows > 0 && columns > 0 && result != NULL) {
    if ((result->matrix = (double **)calloc(
             rows * columns, sizeof(double *) + rows * sizeof(double *))) !=
        NULL) {
      double *ptr = (double *)(result->matrix + rows);
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = ptr + columns * i;
      }
      result->columns = columns;
      result->rows = rows;
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int check_matrix(matrix_t *A) {
  return (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0);
}

void transferMatrix(matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = B->matrix[i][j];
    }
  }
}
