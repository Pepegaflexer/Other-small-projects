#include "test.h"

/*-----pow-----*/
START_TEST(pow_simple_test) {
  double x = 10.5;
  double y = 10.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);
  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_zero_divider_test) {
  double x = 0.0;
  double y = 10.7;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_zero_dividend_test) {
  double x = 10.7;
  double y = 0.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_all_nan_test) {
  double x = NAN;
  double y = NAN;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_pos_inf_divident_test) {
  double x = INFINITY;
  double y = 17.04;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);
  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_all_inf_test) {
  double x = INFINITY;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_pos_inf_divider_test) {
  double x = 17.04;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_neg_inf_divider_test) {
  double x = 17.04;
  double y = -INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_equal_num_test) {
  double x = 565.456451325;
  double y = 565.456451325;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_neg_divider_test) {
  double x = 17.04;
  double y = -2.5;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_zero_inf_test) {
  double x = 0.0;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);
  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_huge_val_small_devider_test) {
  double x = 9007192547409.04234;
  double y = 4000;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);
  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_all_huge_test) {
  double x = 9007192547409.04234;
  double y = 4503596273704.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);
  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_both_zero_test) {
  double x = 0.0;
  double y = 0.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_both_neg_test) {
  double x = -2.0;
  double y = -10.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_pos_loop_test) {
  double x = 1.0;
  double y = 0.54962542;
  for (; x < 10; x += 0.72354736) {
    y += 0.73642;
    long double res1 = s21_pow(x, y);
    long double res2 = pow(x, y);
    ck_assert_double_eq_tol(res1, res2, 1e-4);
  }
}
END_TEST

START_TEST(pow_neg_and_float_test) {
  double x = -6.0;
  double y = 1.54962542;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_neg_and_whole_test) {
  double x = -6.0;
  double y = 2.0;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_neg_inf_test) {
  double x = -INFINITY;
  double y = -INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_inf_var1_test) {
  double x = -INFINITY;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_inf_var2_test) {
  double x = INFINITY;
  double y = -INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(pow_nan_inf_var1_test) {
  double x = NAN;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_nan_inf_var2_test) {
  double x = NAN;
  double y = -INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_nan_inf_var3_test) {
  double x = INFINITY;
  double y = NAN;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_nan_inf_var4_test) {
  double x = -INFINITY;
  double y = NAN;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(pow_neg_x_inf_divider_test) {
  double x = -17.04;
  double y = INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_infinite(res2);
  ck_assert_ldouble_infinite(res1);
}
END_TEST

START_TEST(pow_neg_x_neg_inf_divider_test) {
  double x = -17.04;
  double y = -INFINITY;
  long double res1 = s21_pow(x, y);
  long double res2 = pow(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

Suite *test_pow_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("pow_test");
  /* Core test case */
  tc = tcase_create("pow_tc");

  // pow
  tcase_add_test(tc, pow_simple_test);
  tcase_add_test(tc, pow_zero_divider_test);
  tcase_add_test(tc, pow_zero_dividend_test);
  tcase_add_test(tc, pow_all_nan_test);
  tcase_add_test(tc, pow_pos_inf_divident_test);
  tcase_add_test(tc, pow_all_inf_test);
  tcase_add_test(tc, pow_pos_inf_divider_test);
  tcase_add_test(tc, pow_equal_num_test);
  tcase_add_test(tc, pow_neg_inf_divider_test);
  tcase_add_test(tc, pow_neg_divider_test);
  tcase_add_test(tc, pow_zero_inf_test);
  tcase_add_test(tc, pow_huge_val_small_devider_test);
  tcase_add_test(tc, pow_all_huge_test);
  tcase_add_test(tc, pow_both_zero_test);
  tcase_add_test(tc, pow_both_neg_test);
  tcase_add_test(tc, pow_pos_loop_test);
  tcase_add_test(tc, pow_neg_and_float_test);
  tcase_add_test(tc, pow_neg_and_whole_test);
  tcase_add_test(tc, pow_neg_inf_test);
  tcase_add_test(tc, pow_inf_var1_test);
  tcase_add_test(tc, pow_inf_var2_test);
  tcase_add_test(tc, pow_nan_inf_var1_test);
  tcase_add_test(tc, pow_nan_inf_var2_test);
  tcase_add_test(tc, pow_nan_inf_var3_test);
  tcase_add_test(tc, pow_nan_inf_var4_test);
  tcase_add_test(tc, pow_neg_x_inf_divider_test);
  tcase_add_test(tc, pow_neg_x_neg_inf_divider_test);
  suite_add_tcase(s, tc);

  return s;
}
