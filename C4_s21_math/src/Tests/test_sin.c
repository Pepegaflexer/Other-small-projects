#include "test.h"

/*-----SIN-----*/
START_TEST(sin_pi_zero_res_test) {
  double test = 0.0;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_pi_dev6_test) {
  double test = S21_PI / 6;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_pi_dev4_test) {
  double test = S21_PI / 4;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_pi_dev3_test) {
  double test = S21_PI / 3;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_pi_dev2_test) {
  double test = S21_PI / 2;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_3pi_dev2_test) {
  double test = 3 * S21_PI / 2;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_nan_test) {
  double test = NAN;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sin_inf_test) {
  double test = INFINITY;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sin_inf_negative_test) {
  double test = -INFINITY;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(sin_lopp_test) {
  for (double test = 0.0 + 1e-4; test <= S21_2PI; test += 0.0241575) {
    ck_assert_ldouble_eq_tol(s21_sin(test), sin(test), EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(sin_over_bound_positive_test) {
  double test = 903.0;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_over_bound_negative_test) {
  double test = -423.0;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(sin_close_to_inbound_test) {
  double test = S21_PI - 1e-5;
  long double res1 = s21_sin(test);
  long double res2 = sin(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

Suite *test_sin_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("sin_test");
  /* Core test case */
  tc = tcase_create("sin_tc");

  // sin
  tcase_add_test(tc, sin_pi_zero_res_test);
  tcase_add_test(tc, sin_pi_dev6_test);
  tcase_add_test(tc, sin_pi_dev4_test);
  tcase_add_test(tc, sin_pi_dev3_test);
  tcase_add_test(tc, sin_pi_dev2_test);
  tcase_add_test(tc, sin_3pi_dev2_test);
  tcase_add_test(tc, sin_nan_test);
  tcase_add_test(tc, sin_inf_test);
  tcase_add_test(tc, sin_inf_negative_test);
  tcase_add_test(tc, sin_lopp_test);
  tcase_add_test(tc, sin_over_bound_positive_test);
  tcase_add_test(tc, sin_over_bound_negative_test);
  tcase_add_test(tc, sin_close_to_inbound_test);

  suite_add_tcase(s, tc);

  return s;
}
