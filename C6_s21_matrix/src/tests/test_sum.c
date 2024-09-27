#include "test.h"

START_TEST(test1_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  code += s21_create_matrix(3, 3, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_b[3][3] = {{1., 2., 3.}, {3., 2., 1.}, {7., 5., 2.}};
  double content_e[3][3] = {{2., 4., 6.}, {6., 4., 2.}, {14., 10., 4.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test2_sum) {
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
  double content_e[3][3] = {{7.16351, 7.80907, 9.1823},
                            {12.34937, 5.41829, 8.13568},
                            {10.50111, 10.59072, 2.46306}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test3_sum) {
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
  double content_e[4][4] = {{3.0665, 4.9871, 6.66333, 4.71437},
                            {5.16417, 4.96892, 4.24186, 5.18909},
                            {4.32152, 4.29946, 5.38236, 5.18199},
                            {6.43048, 4.80626, 5.71789, 5.21799}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test4_sum) {
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
  double content_e[3][3] = {{
                                2.,
                                4.,
                                6.,
                            },
                            {6., 9., 12.},
                            {14., 13., 11.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test5_sum) {
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
                            {4., 5., 6.},
                            {7., 8., 9.}};
  double content_b[3][3] = {{
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
                            {7., 7., 7.},
                            {14., 13., 11.}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) a.matrix[y][x] = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&r, &e), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test6_sum) {
  matrix_t a, b, r, e;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(3, 4, &b);
  code += s21_create_matrix(3, 4, &e);
  ck_assert_int_eq(code, 0);
  double content_a[3][4] = {{2.87301, 2.61453, 2.29238, 3.50759},
                            {2.40913, 3.85765, 3.61554, 1.32832},
                            {1.29258, 1.91210, 2.73817, 3.27839}};
  double content_b[3][4] = {{2.33717, 1.05745, 1.54393, 3.49827},
                            {3.77880, 3.53064, 2.34638, 1.33020},
                            {1.06036, 2.70443, 2.43779, 2.89379}};
  double content_e[3][4] = {{5.21018, 3.67198, 3.83631, 7.00586},
                            {6.18793, 7.38829, 5.96192, 2.65852},
                            {2.35294, 4.61653, 5.17596, 6.17218}};
  for (int y = 0; y < a.rows; y++)
    for (int x = 0; x < a.columns; x++) *(a.matrix[y] + x) = content_a[y][x];
  for (int y = 0; y < b.rows; y++)
    for (int x = 0; x < b.columns; x++) b.matrix[y][x] = content_b[y][x];
  for (int y = 0; y < e.rows; y++)
    for (int x = 0; x < e.columns; x++) e.matrix[y][x] = content_e[y][x];

  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_eq_matrix(&e, &r), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&e);
}
END_TEST

START_TEST(test7_sum) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 4, &a);
  code += s21_create_matrix(4, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test8_sum) {
  matrix_t a, b;
  int code = s21_create_matrix(3, 3, &a);
  code += s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test9_sum) {
  matrix_t a, b, r;
  int code = s21_create_matrix(3, 3, &a);
  b.matrix = NULL;
  ck_assert_int_eq(code, 0);
  code = s21_sum_matrix(&a, &b, &r);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

Suite *test_sum_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_SUM_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_sum);
  tcase_add_test(tc, test2_sum);
  tcase_add_test(tc, test3_sum);
  tcase_add_test(tc, test4_sum);
  tcase_add_test(tc, test5_sum);
  tcase_add_test(tc, test6_sum);
  tcase_add_test(tc, test7_sum);
  tcase_add_test(tc, test8_sum);
  tcase_add_test(tc, test9_sum);

  suite_add_tcase(s, tc);

  return s;
}
