#include "test.h"

/*-----atan-----*/
START_TEST(atan_zero_test) {
  double test = 0.0;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_nan_test) {
  double test = NAN;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(atan_inf_test) {
  double test = INFINITY;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_inf_negative_test) {
  double test = -INFINITY;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_pos_bound_test) {
  double test = 1.0;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_neg_bound_test) {
  double test = -1.0;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_pos_over_bound_test) {
  double test = 101.05;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_neg_over_bound_test) {
  double test = -135.05;
  long double res1 = s21_atan(test);
  long double res2 = atan(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_lopp_inbound_test) {
  for (double test = -1.0 + 1e-6; test < 1; test += 0.00241575) {
    long double res1 = s21_atan(test);
    long double res2 = atan(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(atan_lopp_neg_over_bound_test) {
  for (double test = -200; test < -10; test += 2.241563) {
    long double res1 = s21_atan(test);
    long double res2 = atan(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
  for (double test = -10; test < -1; test += 0.0241579) {
    long double res1 = s21_atan(test);
    long double res2 = atan(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(atan_lopp_po_over_bound_test) {
  for (double test = 1 + 1e-6; test < 10; test += 0.0241563) {
    long double res1 = s21_atan(test);
    long double res2 = atan(test);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
  for (double test = 10; test < 200; test += 2.241579) {
    long double res1 = s21_atan(test);
    long double res2 = atan(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_atan_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("atan_test");
  /* Core test case */
  tc = tcase_create("atan_tc");

  // abs
  tcase_add_test(tc, atan_zero_test);
  tcase_add_test(tc, atan_pos_bound_test);
  tcase_add_test(tc, atan_nan_test);
  tcase_add_test(tc, atan_inf_test);
  tcase_add_test(tc, atan_inf_negative_test);
  tcase_add_test(tc, atan_pos_bound_test);
  tcase_add_test(tc, atan_neg_bound_test);
  tcase_add_test(tc, atan_pos_over_bound_test);
  tcase_add_test(tc, atan_neg_over_bound_test);
  tcase_add_test(tc, atan_lopp_inbound_test);
  tcase_add_test(tc, atan_lopp_neg_over_bound_test);
  tcase_add_test(tc, atan_lopp_po_over_bound_test);

  suite_add_tcase(s, tc);

  return s;
}
