#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if ((round(A->matrix[i][j] * pow(10, 7)) / pow(10, 7)) !=
              (round(B->matrix[i][j] * pow(10, 7)) / pow(10, 7))) {
            result = FAILURE;
          }
        }
      }
    } else {
      result = FAILURE;
    }
  } else {
    result = FAILURE;
  }
  return result;
}
