#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

typedef struct s21_matrix {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helpers
int check_matrix(matrix_t *matrix);
void change_rows(matrix_t *A, int x, int b);
void detForDva(matrix_t *A, double *result);
void calcDet(matrix_t *A, double *result, double *sign);
void makeMinor(matrix_t *A, matrix_t *temp, int skipR, int skipC);
void calcComp(matrix_t *A, matrix_t *result, matrix_t *temp);
void transferMatrix(matrix_t *A, matrix_t *B);
void calcCompForDva(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
