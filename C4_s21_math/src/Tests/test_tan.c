#include "test.h"

/*-----tan-----*/
START_TEST(tan_pi_zero_res_test) {
  double test = 0.0;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_pi_dev6_test) {
  double test = S21_PI / 6;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_pi_dev4_test) {
  double test = S21_PI / 4;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_pi_dev3_test) {
  double test = S21_PI / 3;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_nan_test) {
  double test = NAN;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(tan_inf_test) {
  double test = INFINITY;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(tan_inf_negative_test) {
  double test = -INFINITY;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(tan_lopp_test) {
  for (double test = 0.0 + 1e-4; test <= S21_2PI; test += 0.0241575) {
    long double res1 = s21_tan(test);
    long double res2 = tan(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(tan_over_bound_positive_test) {
  double test = 903.0;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_over_bound_negative_test) {
  double test = -423.0;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_close_to_inbound_test) {
  double test = S21_PI - 1e-9;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(tan_close_to_nan_bound_test) {
  double test = S21_PI / 2 - 1e-4;
  long double res1 = s21_tan(test);
  long double res2 = tan(test);
  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

Suite *test_tan_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("tan_test");
  /* Core test case */
  tc = tcase_create("tan_tc");

  // tan
  tcase_add_test(tc, tan_pi_zero_res_test);
  tcase_add_test(tc, tan_pi_dev6_test);
  tcase_add_test(tc, tan_pi_dev4_test);
  tcase_add_test(tc, tan_pi_dev3_test);
  tcase_add_test(tc, tan_nan_test);
  tcase_add_test(tc, tan_inf_test);
  tcase_add_test(tc, tan_inf_negative_test);
  tcase_add_test(tc, tan_lopp_test);
  tcase_add_test(tc, tan_over_bound_positive_test);
  tcase_add_test(tc, tan_over_bound_negative_test);
  tcase_add_test(tc, tan_close_to_inbound_test);
  tcase_add_test(tc, tan_close_to_nan_bound_test);

  suite_add_tcase(s, tc);

  return s;
}
