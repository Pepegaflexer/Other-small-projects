#include "test.h"

START_TEST(test1_det) {
  matrix_t a;
  double d, e = 4;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test2_det) {
  matrix_t a;
  double d, e = 289.000344808923674;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test3_det) {
  matrix_t a;
  double d, e = 0;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_det) {
  matrix_t a;
  double d, e = 11.70006167326680176888;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test5_det) {
  matrix_t a;
  double d;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_det) {
  matrix_t a;
  double d;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_det) {
  ck_assert_int_eq(s21_determinant(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_det) {
  matrix_t a;
  double d, e = 24.11167307304728580683610306381957237;
  int code = s21_create_matrix(7, 7, &a);
  ck_assert_int_eq(code, 0);
  double content_a[7][7] = {
      {3.54155, 2.53027, 2.52268, 3.32609, 1.74077, 1.84826, 2.31548},
      {1.79850, 1.03137, 3.21930, 2.23851, 3.69014, 1.86757, 2.58197},
      {3.12373, 2.50464, 2.81140, 3.95159, 3.93592, 2.55369, 2.85939},
      {2.53200, 2.17887, 3.89360, 2.57050, 1.35048, 2.86216, 2.85716},
      {2.45656, 2.44057, 3.60225, 2.02151, 2.66313, 3.54608, 1.99800},
      {2.73763, 3.62892, 3.16649, 1.46655, 1.63051, 3.30205, 1.16198},
      {2.99739, 1.10405, 3.75781, 1.69789, 2.66463, 2.54331, 1.13451}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test9_det) {
  matrix_t a;
  double d, e = 0;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {1., 2., 3.}, {7., 8., 9.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test10_det) {
  matrix_t a;
  double d, e = 5;
  int code = s21_create_matrix(1, 1, &a);
  ck_assert_int_eq(code, 0);
  a.matrix[0][0] = 5;
  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}

START_TEST(test11_det) {
  matrix_t a;
  double d, e = -202;
  int code = s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(code, 0);
  double content_a[2][2] = {{10., 34.}, {13., 24.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test12_det) {
  matrix_t a;
  double d, e = 1947;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {
      {7, 5, 6, 1}, {0, 4, 7, 2}, {9, 0, 1, 4}, {8, 6, 0, 7}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_determinant(&a, &d);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(d, e, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

Suite *test_det_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_DETERMINANT_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_det);
  tcase_add_test(tc, test2_det);
  tcase_add_test(tc, test3_det);
  tcase_add_test(tc, test4_det);
  tcase_add_test(tc, test5_det);
  tcase_add_test(tc, test6_det);
  tcase_add_test(tc, test7_det);
  tcase_add_test(tc, test8_det);
  tcase_add_test(tc, test9_det);
  tcase_add_test(tc, test10_det);
  tcase_add_test(tc, test11_det);
  tcase_add_test(tc, test12_det);

  suite_add_tcase(s, tc);

  return s;
}
