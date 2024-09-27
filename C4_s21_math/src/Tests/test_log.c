#include "test.h"

/*-----log-----*/
START_TEST(log_simple_test) {
  double test = 0.5;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(log_nan_test) {
  double test = S21_NAN;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(log_pos_inf_test) {
  double test = INFINITY;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(log_neg_inf_test) {
  double test = -INFINITY;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(log_zero_test) {
  double test = 0.0;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(log_one_value_test) {
  double test = 1.0;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(log_neg_value_test) {
  double test = -461.6;
  long double res1 = s21_log(test);
  long double res2 = log(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(log_loop_less_one_test) {
  for (double test = 0 + 1e-8; test < 1; test += 0.00241563) {
    long double res1 = s21_log(test);
    long double res2 = log(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(log_loop_larger_one_test) {
  for (double test = 1 + 1e-8; test < 2107483647; test += 949355.07241564963) {
    long double res1 = s21_log(test);
    long double res2 = log(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(log_loop_whole_num_test) {
  for (double test = 2; test < 2107483610; test += 949355) {
    long double res1 = s21_log(test);
    long double res2 = log(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_log_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("log_test");
  /* Core test case */
  tc = tcase_create("log_tc");

  tcase_add_test(tc, log_simple_test);
  tcase_add_test(tc, log_nan_test);
  tcase_add_test(tc, log_pos_inf_test);
  tcase_add_test(tc, log_neg_inf_test);
  tcase_add_test(tc, log_zero_test);
  tcase_add_test(tc, log_one_value_test);
  tcase_add_test(tc, log_neg_value_test);
  tcase_add_test(tc, log_loop_less_one_test);
  tcase_add_test(tc, log_loop_larger_one_test);
  tcase_add_test(tc, log_loop_whole_num_test);

  suite_add_tcase(s, tc);

  return s;
}