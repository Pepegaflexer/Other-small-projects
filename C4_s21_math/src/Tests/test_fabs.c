#include "test.h"

/*-----FABS-----*/
START_TEST(fabs_negative_test) {
  double test = -50.0;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(fabs_positive_test) {
  double test = 650.0;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(fabs_zero_test) {
  double test = 0.0;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(fabs_double_min_test) {
  double test = -9223372036854775808.0;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(fabs_loop_test) {
  for (double test = -214600.0; test <= 214600.0; test += 1007.0452525235) {
    long double res1 = s21_fabs(test);
    long double res2 = fabs(test);
    ck_assert_ldouble_eq(res1, res2);
  }
}
END_TEST

START_TEST(fabs_inf_test) {
  double test = INFINITY;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(fabs_neg_inf_test) {
  double test = -INFINITY;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(fabs_nan_test) {
  double test = -NAN;
  long double res1 = s21_fabs(test);
  long double res2 = fabs(test);
  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

Suite *test_fabs_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("fabs_test");
  /* Core test case */
  tc = tcase_create("fabs_tc");

  // abs
  tcase_add_test(tc, fabs_negative_test);
  tcase_add_test(tc, fabs_positive_test);
  tcase_add_test(tc, fabs_zero_test);
  tcase_add_test(tc, fabs_double_min_test);
  tcase_add_test(tc, fabs_loop_test);
  tcase_add_test(tc, fabs_inf_test);
  tcase_add_test(tc, fabs_neg_inf_test);
  tcase_add_test(tc, fabs_nan_test);

  suite_add_tcase(s, tc);

  return s;
}
