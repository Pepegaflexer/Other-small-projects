#include "test.h"

START_TEST(test1_mul_num) {
  matrix_t a, r, e;
  double m = 2.;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 2., 1.},
                            {7., 5., 2.}};
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {6., 4., 2.},
                            {14., 10., 4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{0.0966490000, 2.8702450000, 4.9310520000},
                            {3.7267510000, 1.1966990000, 4.1984180000},
                            {2.4329690000, 4.8174000000, 0.2275840000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {
      {1.2626390000, 2.7570900000, 2.1940030000, 1.5970850000},
      {0.9751490000, 0.7391020000, 1.5494990000, 1.5430800000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_mul_num) {
  matrix_t a, r, e;
  double m = 0.7;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[3][4] = {
      {1.2626390000, 2.7570900000, 2.1940030000, 1.5970850000},
      {0.9751490000, 0.7391020000, 1.5494990000, 1.5430800000},
      {1.9202610000, 1.6892750000, 2.7076350000, 1.9110910000}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_mul_num) {
  matrix_t a, r, e;
  double m = 0;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_mul_num) {
  matrix_t a, r;
  double m = 0;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;

  code = s21_mult_number(&a, m, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_mul_num) {
  ck_assert_int_eq(s21_mult_number(NULL, 1.3, NULL), INCORRECT_MATRIX);
}
END_TEST

Suite *test_mul_num_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_MUL_NUM_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_mul_num);
  tcase_add_test(tc, test2_mul_num);
  tcase_add_test(tc, test3_mul_num);
  tcase_add_test(tc, test4_mul_num);
  tcase_add_test(tc, test5_mul_num);
  tcase_add_test(tc, test6_mul_num);
  tcase_add_test(tc, test7_mul_num);

  suite_add_tcase(s, tc);

  return s;
}
