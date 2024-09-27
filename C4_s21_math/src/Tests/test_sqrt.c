#include "test.h"

/*-----sqrt-----*/

START_TEST(sqrt_1) {
  double num = 0.0;
  ck_assert_ldouble_eq_tol(sqrt(num), s21_sqrt(num), EPS_FOR_TEST);
}
END_TEST

START_TEST(sqrt_2) {
  double num = 0.3;
  ck_assert_ldouble_eq_tol(sqrt(num), s21_sqrt(num), EPS_FOR_TEST);
}
END_TEST

START_TEST(sqrt_3) {
  double num = 103;
  ck_assert_ldouble_eq_tol(sqrt(num), s21_sqrt(num), EPS_FOR_TEST);
}
END_TEST

START_TEST(sqrt_4) {
  double test = -0.5;
  long double res1 = s21_sqrt(test);
  long double res2 = sqrt(test);
  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sqrt_5) {
  double test = INFINITY;
  long double res1 = s21_sqrt(test);
  long double res2 = sqrt(test);
  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(sqrt_6) {
  double test = -INFINITY;
  long double res1 = s21_sqrt(test);
  long double res2 = sqrt(test);
  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sqrt_7) {
  double test = NAN;
  long double res1 = s21_sqrt(test);
  long double res2 = sqrt(test);
  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sqrt_float_loop_test) {
  for (double test = 0.0; test < 20; test += 0.10649355) {
    long double res1 = s21_sqrt(test);
    long double res2 = sqrt(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(sqrt_whole_loop_test) {
  for (double test = 0.0; test < 800; test += 3) {
    long double res1 = s21_sqrt(test);
    long double res2 = sqrt(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(sqrt_whole_float_loop_test) {
  for (double test = 0.0; test < 800; test += 2.5) {
    long double res1 = s21_sqrt(test);
    long double res2 = sqrt(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(sqrt_large_float_loop_test) {
  for (double test = 0.0; test < 2107483610; test += 949355.07241564963) {
    long double res1 = s21_sqrt(test);
    long double res2 = sqrt(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(sqrt_small_float_loop_test) {
  for (double test = 0.0; test < 1; test += 0.0007241564963) {
    long double res1 = s21_sqrt(test);
    long double res2 = sqrt(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_sqrt_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("sqrt_test");
  /* Core test case */
  tc = tcase_create("sqrt_tc");

  // sqrt
  tcase_add_test(tc, sqrt_1);
  tcase_add_test(tc, sqrt_2);
  tcase_add_test(tc, sqrt_3);
  tcase_add_test(tc, sqrt_4);
  tcase_add_test(tc, sqrt_5);
  tcase_add_test(tc, sqrt_6);
  tcase_add_test(tc, sqrt_7);
  tcase_add_test(tc, sqrt_float_loop_test);
  tcase_add_test(tc, sqrt_whole_loop_test);
  tcase_add_test(tc, sqrt_whole_float_loop_test);
  tcase_add_test(tc, sqrt_large_float_loop_test);
  tcase_add_test(tc, sqrt_small_float_loop_test);

  suite_add_tcase(s, tc);

  return s;
}