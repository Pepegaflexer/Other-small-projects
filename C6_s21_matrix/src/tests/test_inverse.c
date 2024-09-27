#include "test.h"

START_TEST(test1_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {
      {-0.25, 2.75, -1.}, {0.25, -4.75, 2.}, {0.25, 2.25, -1.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_e[3][3] = {{-0.1409016702, 0.1631353754, 0.0434255769},
                            {0.0661426507, -0.0845638486, 0.1269049405},
                            {0.1062191989, 0.0460250861, -0.0747194127}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.29065, 3.09765, 1.84139, 3.86339}};
  double content_e[4][4] = {
      {-0.6892499107, -1.6362600080, 1.2909415507, 0.4284039249},
      {0.3588626362, -0.3777606089, -0.1150224313, 0.0848991764},
      {0.2706058939, 0.7498401502, -0.1659167199, -0.4704092234},
      {-0.0080477312, 0.9156520525, -0.5941100018, 0.1609714411}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test6_inverse) {
  matrix_t a, r;
  int code = s21_create_matrix(3, 4, &a);
  ck_assert_int_eq(code, 0);
  a.columns = -1;
  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test7_inverse) {
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {1., 2., 4.}, {7., 5., 2.}};
  double content_e[3][3] = {{-1.7777777778, 1.2222222222, 0.2222222222},
                            {2.8888888889, -2.1111111111, -0.1111111111},
                            {-1., 1., 0.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test9_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(2, 2, &a);
  code += s21_create_matrix(2, 2, &e);
  ck_assert_int_eq(code, 0);
  double content_a[2][2] = {{0., 3.}, {4., 5.}};
  double content_e[2][2] = {{-0.41666666666, 0.25}, {0.33333333333, 0.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test10_inverse) {
  matrix_t a, r, e;
  int code = s21_create_matrix(1, 1, &a);
  code += s21_create_matrix(1, 1, &e);
  ck_assert_int_eq(code, 0);
  double content_a[2][2] = {{
      5,
  }};
  double content_e[2][2] = {{0.2}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_inverse_matrix(&a, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

Suite *test_inv_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_INVERSE_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_inverse);
  tcase_add_test(tc, test2_inverse);
  tcase_add_test(tc, test3_inverse);
  tcase_add_test(tc, test4_inverse);
  tcase_add_test(tc, test5_inverse);
  tcase_add_test(tc, test6_inverse);
  tcase_add_test(tc, test7_inverse);
  tcase_add_test(tc, test8_inverse);
  tcase_add_test(tc, test9_inverse);
  tcase_add_test(tc, test10_inverse);

  suite_add_tcase(s, tc);

  return s;
}
