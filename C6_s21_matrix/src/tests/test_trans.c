#include "test.h"

START_TEST(test1_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{1., 3., 7.}, {2., 2., 5.}, {3., 1., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{0.13807, 5.32393, 3.47567},
                            {4.10035, 1.70957, 6.882},
                            {7.04436, 5.99774, 0.32512}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {{1.80377, 1.39307, 2.74323, 2.74323},
                            {3.9387, 1.05586, 2.41325, 2.41325},
                            {3.13429, 2.21357, 3.86805, 3.86805},
                            {2.28155, 2.2044, 2.73013, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_transpose) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][3] = {{1.80377, 1.39307, 2.74323},
                            {3.9387, 1.05586, 2.41325},
                            {3.13429, 2.21357, 3.86805},
                            {2.28155, 2.2044, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
// END_TEST

START_TEST(test5_transpose) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_transpose(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_transpose) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

Suite *test_trans_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_TRANSPOSE_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_transpose);
  tcase_add_test(tc, test2_transpose);
  tcase_add_test(tc, test3_transpose);
  tcase_add_test(tc, test4_transpose);
  tcase_add_test(tc, test5_transpose);
  tcase_add_test(tc, test6_transpose);

  suite_add_tcase(s, tc);

  return s;
}
