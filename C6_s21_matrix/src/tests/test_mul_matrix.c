#include "test.h"

START_TEST(test1_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_b[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{28, 21, 11}, {16, 15, 13}, {36, 34, 30}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  double content_e[3][3] = {{79.2664939, 41.8446718, 24.1219067},
                            {91.5501947, 48.3292204, 27.8600092},
                            {75.0513002, 39.6194769, 22.8391641}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  double content_e[4][4] = {{30.4903699, 28.6751430, 23.3211914, 29.5050635},
                            {17.3626542, 15.0425472, 14.4876085, 17.4521057},
                            {28.7361424, 26.1483774, 25.4834697, 30.1526862},
                            {28.7361424, 26.1483774, 25.4834697, 30.1526862}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {2., 4., 6.},
                            {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_e[3][3] = {{30, 36, 42}, {60, 72, 84}, {41, 55, 69}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  double content_b[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{28, 21, 11}, {61, 48, 29}, {94, 75, 47}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_mult_matr) {
  matrix_t a, b, r, e;
  int code = code = s21_create_matrix(2, 5, &a);
  code += s21_create_matrix(5, 2, &b);
  code += s21_create_matrix(2, 2, &e);
  ck_assert_int_eq(code, 0);
  double content_a[2][5] = {{2.15746, 1.61630, 2.02538, 1.24788, 1.55167},
                            {3.91035, 1.25229, 3.80819, 1.16017, 3.14779}};
  double content_b[5][2] = {{1.55365, 3.68359},
                            {3.58831, 3.84431},
                            {1.41244, 1.80059},
                            {2.20100, 3.95030},
                            {1.89133, 2.32189}};
  double content_e[2][2] = {{17.6937548103, 26.3399427289},
                            {24.4548037217, 37.9671476326}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test7_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(5, 2, &a);
  code += s21_create_matrix(2, 4, &b);
  code += s21_create_matrix(5, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[5][2] = {{1.55365, 3.68359},
                            {3.58831, 3.84431},
                            {1.41244, 1.80059},
                            {2.20100, 3.95030},
                            {1.89133, 2.32189}};
  double content_b[2][4] = {{2.19891, 2.44875, 3.21633, 1.14803},
                            {2.44390, 3.74607, 2.08689, 3.85980}};
  double content_e[5][4] = {
      {12.4186621225, 17.6034864288, 12.6842982396, 16.0015574915},
      {17.2854799511, 23.1879284742, 19.5638411982, 18.9577552673},
      {7.5062903414, 10.2038486313, 8.3005064103, 8.5714407752},
      {14.4939390800, 20.1877990710, 15.3229838970, 17.7741819700},
      {9.8333314213, 13.3293568098, 10.9286704410, 11.1333346019}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test8_mult_matr) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{3.78308, 2.33718, 2.59181, 3.94461},
                            {3.40176, 2.38731, 1.51887, 1.09706},
                            {2.68414, 1.05042, 1.42217, 1.54185}};
  double content_b[4][3] = {{3.00266, 3.60228, 2.78362},
                            {2.52415, 1.90470, 2.74344},
                            {1.95798, 3.50581, 2.10471},
                            {1.93363, 1.23257, 2.47293}};
  double content_e[3][3] = {{29.9608243, 32.0277415, 32.1523231},
                            {21.3354824, 23.4782742, 21.9283824},
                            {16.4769253, 18.5560547, 17.1595326}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test9_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test10_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(5, 2, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);

  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test11_mult_matr) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_mult_matrix(&a, &b, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test12_mult_matr) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  code = s21_mult_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

Suite *test_mul_mat_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_MUL_MAT_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_mult_matr);
  tcase_add_test(tc, test2_mult_matr);
  tcase_add_test(tc, test3_mult_matr);
  tcase_add_test(tc, test4_mult_matr);
  tcase_add_test(tc, test5_mult_matr);
  tcase_add_test(tc, test6_mult_matr);
  tcase_add_test(tc, test7_mult_matr);
  tcase_add_test(tc, test8_mult_matr);
  tcase_add_test(tc, test9_mult_matr);
  tcase_add_test(tc, test10_mult_matr);
  tcase_add_test(tc, test11_mult_matr);
  tcase_add_test(tc, test12_mult_matr);

  suite_add_tcase(s, tc);

  return s;
}
