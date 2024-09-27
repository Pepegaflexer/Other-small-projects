#include "test.h"

/*-----acos-----*/
START_TEST(acos_zero_test) {
  double test = 0.0;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(acos_nan_test) {
  double test = NAN;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(acos_inf_test) {
  double test = INFINITY;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(acos_inf_negative_test) {
  double test = -INFINITY;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(acos_pos_bound_test) {
  double test = 1.0;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(acos_neg_bound_test) {
  double test = -1.0;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(acos_pos_over_bound_test) {
  double test = 101.05;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(acos_neg_over_bound_test) {
  double test = -135.05;
  long double res1 = s21_acos(test);
  long double res2 = acos(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(acos_lopp_test) {
  for (double test = -1.0 + 1e-9; test < 1; test += 0.00241575) {
    ck_assert_ldouble_eq_tol(s21_acos(test), acos(test), EPS_FOR_TEST);
  }
}
END_TEST
Suite *test_acos_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("acos_test");
  /* Core test case */
  tc = tcase_create("acos_tc");

  // abs
  tcase_add_test(tc, acos_zero_test);
  tcase_add_test(tc, acos_pos_bound_test);
  tcase_add_test(tc, acos_nan_test);
  tcase_add_test(tc, acos_inf_test);
  tcase_add_test(tc, acos_inf_negative_test);
  tcase_add_test(tc, acos_pos_bound_test);
  tcase_add_test(tc, acos_neg_bound_test);
  tcase_add_test(tc, acos_pos_over_bound_test);
  tcase_add_test(tc, acos_neg_over_bound_test);
  tcase_add_test(tc, acos_lopp_test);

  suite_add_tcase(s, tc);

  return s;
}
