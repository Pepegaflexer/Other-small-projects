#include "test.h"

/*-----EXP-----*/
START_TEST(exp_negative_test) {
  double test = -3.0;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_positive_test) {
  double test = 7.0;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);
  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_nan_test) {
  double test = NAN;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_nan(res2);
  ck_assert_ldouble_nan(res1);
}
END_TEST

START_TEST(exp_infinity_test) {
  double test = INFINITY;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(exp_minus_infinity_test) {
  double test = INFINITY;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(exp_DBLMAX_test) {
  double test = S21_DBL_MAX;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(exp_minus_DBLMAX_test) {
  double test = -S21_DBL_MAX;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_big_positive_test) {
  double test = 1000;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(exp_big_neagtive_test) {
  double test = -1000000;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_small_pos_number_test) {
  double test = 0.000000000001;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_small_neg_number_test) {
  double test = -0.000000000001;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_null_test) {
  double test = 0;
  long double res1 = s21_exp(test);
  long double res2 = exp(test);

  ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
}
END_TEST

START_TEST(exp_small_float_loop_test) {
  for (double test = 0.0; test < 1; test += 0.0007241564963) {
    long double res1 = s21_exp(test);
    long double res2 = exp(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(exp_float_loop_test) {
  for (double test = 0.0; test < 20; test += 0.10649355) {
    long double res1 = s21_exp(test);
    long double res2 = exp(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(exp_whole_loop_test) {
  for (double test = 0.0; test < 29; test += 1) {
    long double res1 = s21_exp(test);
    long double res2 = exp(test);
    ck_assert_ldouble_eq_tol(res1, res2, 1e-3);
  }
}
END_TEST

START_TEST(exp_whole_neg_loop_test) {
  for (double test = -100; test < 0; test += 1) {
    long double res1 = s21_exp(test);
    long double res2 = exp(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

START_TEST(exp_float_neg_loop_test) {
  for (double test = -20.0; test < 0; test += 0.10649355) {
    long double res1 = s21_exp(test);
    long double res2 = exp(test);

    ck_assert_ldouble_eq_tol(res1, res2, EPS_FOR_TEST);
  }
}
END_TEST

Suite *test_exp_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("exp_test");
  /* Core test case */
  tc = tcase_create("exp_tc");

  // exp
  tcase_add_test(tc, exp_negative_test);
  tcase_add_test(tc, exp_positive_test);
  tcase_add_test(tc, exp_nan_test);
  tcase_add_test(tc, exp_infinity_test);
  tcase_add_test(tc, exp_minus_infinity_test);
  tcase_add_test(tc, exp_DBLMAX_test);
  tcase_add_test(tc, exp_minus_DBLMAX_test);
  tcase_add_test(tc, exp_big_positive_test);
  tcase_add_test(tc, exp_big_neagtive_test);
  tcase_add_test(tc, exp_small_pos_number_test);
  tcase_add_test(tc, exp_small_neg_number_test);
  tcase_add_test(tc, exp_null_test);
  tcase_add_test(tc, exp_small_float_loop_test);
  tcase_add_test(tc, exp_float_loop_test);
  tcase_add_test(tc, exp_whole_loop_test);
  tcase_add_test(tc, exp_whole_neg_loop_test);
  tcase_add_test(tc, exp_float_neg_loop_test);

  suite_add_tcase(s, tc);

  return s;
}
