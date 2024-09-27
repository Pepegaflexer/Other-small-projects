#include "test.h"

/*-----cos-----*/
START_TEST(cos_pi_zero_res_test) {
  double test = 0.0;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_pi_dev6_test) {
  double test = S21_PI / 6;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_pi_dev4_test) {
  double test = S21_PI / 4;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_pi_dev3_test) {
  double test = S21_PI / 3;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_2pi_test) {
  double test = S21_2PI;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_pi_test) {
  double test = S21_PI;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_nan_test) {
  double test = NAN;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(cos_inf_test) {
  double test = INFINITY;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(cos_inf_negative_test) {
  double test = -INFINITY;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(cos_lopp_test) {
  for (double test = 0.0 + 1e-4; test <= S21_2PI; test += 0.0241575) {
    ck_assert_ldouble_eq_tol(s21_cos(test), cos(test), EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(cos_over_bound_positive_test) {
  double test = 903.0;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_over_bound_negative_test) {
  double test = -423.0;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(cos_close_to_inbound_test) {
  double test = S21_PI - 1e-5;
  long double res1 = s21_cos(test);
  long double res2 = cos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

Suite *test_cos_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("cos_test");
  /* Core test case */
  tc = tcase_create("cos_tc");

  // cos
  tcase_add_test(tc, cos_pi_zero_res_test);
  tcase_add_test(tc, cos_pi_dev6_test);
  tcase_add_test(tc, cos_pi_dev4_test);
  tcase_add_test(tc, cos_pi_dev3_test);
  tcase_add_test(tc, cos_2pi_test);
  tcase_add_test(tc, cos_pi_test);
  tcase_add_test(tc, cos_nan_test);
  tcase_add_test(tc, cos_inf_test);
  tcase_add_test(tc, cos_inf_negative_test);
  tcase_add_test(tc, cos_lopp_test);
  tcase_add_test(tc, cos_over_bound_positive_test);
  tcase_add_test(tc, cos_over_bound_negative_test);
  tcase_add_test(tc, cos_close_to_inbound_test);

  suite_add_tcase(s, tc);

  return s;
}
