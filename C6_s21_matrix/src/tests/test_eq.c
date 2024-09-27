#include "test.h"

START_TEST(test1_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_b[3][3] = {{
                                1.,
                                2.,
                                3.,
                            },
                            {3., 1., 1.},
                            {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test2_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{0.13807, 4.10035, 7.04436},
                            {5.32393, 1.70957, 5.99774},
                            {3.47567, 6.88200, 0.32512}};
  double content_b[3][3] = {{7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794},
                            {7.02544, 3.70872, 2.13794}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test3_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.26273, 1.04840, 3.52904, 2.43282},
                            {3.77110, 3.91306, 2.02829, 2.98469},
                            {1.57829, 1.88621, 1.51431, 2.45186},
                            {3.68725, 2.39301, 1.84984, 2.48786}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test4_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
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
                            {2., 4., 6.},
                            {7., 5., 2.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test5_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(4, 4, &a);
  code += s21_create_matrix(4, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  double content_b[4][4] = {{1.80377, 3.93870, 3.13429, 2.28155},
                            {1.39307, 1.05586, 2.21357, 2.20440},
                            {2.74323, 2.41325, 3.86805, 2.73013},
                            {2.74323, 2.41325, 3.86805, 2.73013}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test6_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.33717, 1.05745, 1.54393, 3.49827},
                            {3.77880, 3.53064, 2.34638, 1.33020},
                            {1.06036, 2.70443, 2.43779, 2.89379}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test7_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test8_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test9_eq) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test10_eq) { ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0); }
END_TEST

Suite *test_eq_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_EQUAL_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_eq);
  tcase_add_test(tc, test2_eq);
  tcase_add_test(tc, test3_eq);
  tcase_add_test(tc, test4_eq);
  tcase_add_test(tc, test5_eq);
  tcase_add_test(tc, test6_eq);
  tcase_add_test(tc, test7_eq);
  tcase_add_test(tc, test8_eq);
  tcase_add_test(tc, test9_eq);
  tcase_add_test(tc, test10_eq);

  suite_add_tcase(s, tc);

  return s;
}