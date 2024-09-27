#ifndef SRC_C_SOURCE_3D_VIEWER_H
#define SRC_C_SOURCE_3D_VIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

typedef struct matrix {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int num_of_ver_in_facets;
} polygon_t;

typedef struct data_struct {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
  double minMaxX[2];
  double minMaxY[2];
  double minMaxZ[2];
} dataStruct;

void reader(dataStruct *srcData, char *path);

void sumPointPoly(dataStruct *srcData, char *path, regex_t regex_v,
                  regex_t regex_f);
void parserObj(dataStruct *srcData, char *path, regex_t regex_v,
               regex_t regex_f);
void fromFileToFacet(int *vertexes, int num_of_ver_in_facets, int *forF);
void findMinMaxX(dataStruct *srcData);
void findMinMaxY(dataStruct *srcData);
void findMinMaxZ(dataStruct *srcData);
void freeData(dataStruct *srcData);

// matrix
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int check_matrix(matrix_t *A);

// helpers
int isDigit(char c);

#ifdef __cplusplus
}
#endif

#endif  // SRC_C_SOURCE_3D_VIEWER_H
