#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  double det = 0.0;
  matrix_t temp = {0};
  matrix_t trans = {0};
  if (check_matrix(A) && result != NULL) {
    if (A->rows == A->columns) {
      s21_determinant(A, &det);
      if (det != 0) {
        error = s21_calc_complements(A, &temp);
        if (error == 0) {
          error = s21_transpose(&temp, &trans);
          s21_remove_matrix(&temp);
          if (error == 0) {
            error = s21_mult_number(&trans, 1.0 / det, result);
            s21_remove_matrix(&trans);
          }
        }
      } else {
        error = CALC_ERROR;
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}
