#include "test.h"

/*-----fmod-----*/
START_TEST(fmod_simple_test) {
  double x = 10.5;
  double y = 10.0;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_zero_divider_test) {
  double x = 0.01;
  double y = 10.7;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_zero_dividend_test) {
  double x = 10.7;
  double y = 0.0;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(fmod_all_nan_test) {
  double x = NAN;
  double y = NAN;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(fmod_pos_inf_divident_test) {
  double x = INFINITY;
  double y = 17.04;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(fmod_all_inf_test) {
  double x = INFINITY;
  double y = INFINITY;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(fmod_pos_inf_divider_test) {
  double x = 17.04;
  double y = INFINITY;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_neg_inf_divider_test) {
  double x = 17.04;
  double y = -INFINITY;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_equal_num_test) {
  double x = 565.456451325;
  double y = 565.456451325;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_neg_divider_test) {
  double x = 17.04;
  double y = -3.9;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_zero_inf_test) {
  double x = 0.0;
  double y = INFINITY;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_cross_loop_test) {
  double x = -100.2357826239;
  double y = 100.54962542;
  for (; x < 100; x += 1.235436) {
    y -= 3.3642;
    long double res1 = s21_fmod(x, y);
    long double res2 = fmod(x, y);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(fmod_huge_val_small_devider_test) {
  double x = 9007192547409.04234;
  double y = 4000;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);
  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_all_huge_test) {
  double x = 9007192547409.04234;
  double y = 4503596273704.0;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(fmod_both_zero_test) {
  double x = 0.0;
  double y = 0.0;
  long double res1 = s21_fmod(x, y);
  long double res2 = fmod(x, y);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(fmod_neg_loop_test) {
  double x = -1000.2357826239;
  double y = -102.54962542;
  for (; x < 0; x += 7.2354736) {
    y += 0.73642;
    long double res1 = s21_fmod(x, y);
    long double res2 = fmod(x, y);
    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(fmod_pos_loop_test) {
  double x = 1000.2357826239;
  double y = 102.54962542;
  for (; x > 0; x -= 7.2354736) {
    y -= 0.73642;
    long double res1 = s21_fmod(x, y);
    long double res2 = fmod(x, y);
    ck_assert_double_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_fmod_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("fmod_test");
  /* Core test case */
  tc = tcase_create("fmod_tc");

  // fmod
  tcase_add_test(tc, fmod_simple_test);
  tcase_add_test(tc, fmod_zero_divider_test);
  tcase_add_test(tc, fmod_zero_dividend_test);
  tcase_add_test(tc, fmod_all_nan_test);
  tcase_add_test(tc, fmod_pos_inf_divident_test);
  tcase_add_test(tc, fmod_all_inf_test);
  tcase_add_test(tc, fmod_pos_inf_divider_test);
  tcase_add_test(tc, fmod_equal_num_test);
  tcase_add_test(tc, fmod_neg_inf_divider_test);
  tcase_add_test(tc, fmod_neg_divider_test);
  tcase_add_test(tc, fmod_zero_inf_test);
  tcase_add_test(tc, fmod_cross_loop_test);
  tcase_add_test(tc, fmod_huge_val_small_devider_test);
  tcase_add_test(tc, fmod_all_huge_test);
  tcase_add_test(tc, fmod_both_zero_test);
  tcase_add_test(tc, fmod_neg_loop_test);
  tcase_add_test(tc, fmod_pos_loop_test);

  suite_add_tcase(s, tc);

  return s;
}
