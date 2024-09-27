#include "test.h"

/*-----ceil-----*/
START_TEST(ceil_simple_test) {
  double test = 100.423;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(ceil_zero_test) {
  double test = 0.0;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(ceil_zero_float_test) {
  double test = 0.231;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(ceil_nan_test) {
  double test = NAN;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(ceil_pos_inf_test) {
  double test = INFINITY;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(ceil_neg_inf_test) {
  double test = -INFINITY;
  long double res1 = s21_ceil(test);
  long double res2 = ceil(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(ceil_pos_loop_test) {
  for (double test = 1.1293; test <= 1000.0; test += 10.0452525235) {
    long double res1 = s21_ceil(test);
    long double res2 = ceil(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(ceil_neg_loop_test) {
  for (double test = -1000.013; test <= -1.0; test += 10.0452525235) {
    long double res1 = s21_ceil(test);
    long double res2 = ceil(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(ceil_zero_loop_test) {
  for (double test = -0.999999; test <= 1.0; test += 0.0452525235) {
    long double res1 = s21_ceil(test);
    long double res2 = ceil(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(ceil_no_float_loop_test) {
  for (double test = -100; test <= 100; test += 1) {
    long double res1 = s21_ceil(test);
    long double res2 = ceil(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_ceil_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("ceil_test");
  /* Core test case */
  tc = tcase_create("ceil_tc");

  // ceil
  tcase_add_test(tc, ceil_simple_test);
  tcase_add_test(tc, ceil_zero_test);
  tcase_add_test(tc, ceil_zero_float_test);
  tcase_add_test(tc, ceil_nan_test);
  tcase_add_test(tc, ceil_pos_inf_test);
  tcase_add_test(tc, ceil_neg_inf_test);
  tcase_add_test(tc, ceil_pos_loop_test);
  tcase_add_test(tc, ceil_neg_loop_test);
  tcase_add_test(tc, ceil_zero_loop_test);
  tcase_add_test(tc, ceil_no_float_loop_test);

  suite_add_tcase(s, tc);

  return s;
}
