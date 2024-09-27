#include "test.h"

START_TEST(test1_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{-1., 1., 1.}, {11., -19., 9.}, {-4., 8., -4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{-40.7206312816, 19.1152488642, 30.6973850981},
                            {47.1461797280, -24.4389814028, 13.3012657445},
                            {12.5500066838, 36.6755715730, -21.5939360456}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_e[4][4] = {
      {0., 0., 0., 0.},
      {0., 0., 0., 0.},
      {-5.0123523428, -0.9933255993, 5.5038169258, -1.8833757880},
      {5.0123523428, 0.9933255993, -5.5038169258, 1.8833757880}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  double content_e[4][4] = {
      {-8.0642664633, 4.1987149757, 3.1661056480, -0.0941589509},
      {-19.1443430067, -4.4198224214, 8.7731760020, 10.7131854857},
      {15.1040957594, -1.3457695400, -1.9412358558, -6.9511236616},
      {5.0123523428, 0.9933255993, -5.5038169258, 1.8833757880}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_complement) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_complement) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_complement) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(2, 2, &a);
  code += s21_create_matrix(2, 2, &e);
  ck_assert_int_eq(code, 0);
  double content_a[2][2] = {{0., 3.}, {4., 5.}};
  double content_e[2][2] = {{5., -4.}, {-3., 0.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test9_complement) {
  matrix_t a, r, e;
  int code = s21_create_matrix(1, 1, &a);
  code += s21_create_matrix(1, 1, &e);
  ck_assert_int_eq(code, 0);
  double content_a[1][1] = {{
      100,
  }};
  double content_e[1][1] = {{1.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_calc_complements(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

Suite *test_compl_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_CALC_COMPL_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_complement);
  tcase_add_test(tc, test2_complement);
  tcase_add_test(tc, test3_complement);
  tcase_add_test(tc, test4_complement);
  tcase_add_test(tc, test5_complement);
  tcase_add_test(tc, test6_complement);
  tcase_add_test(tc, test7_complement);
  tcase_add_test(tc, test8_complement);
  tcase_add_test(tc, test9_complement);

  suite_add_tcase(s, tc);

  return s;
}
