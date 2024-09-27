#include "test.h"

/*-----floor-----*/
START_TEST(floor_simple_test) {
  double test = 100.523;
  long double res1 = s21_floor(test);
  long double res2 = floor(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(floor_zero_test) {
  double test = 0.0;
  long double res1 = s21_floor(test);
  long double res2 = floor(test);

  ck_assert_ldouble_eq(res1, res2);
}
END_TEST

START_TEST(floor_nan_test) {
  double test = NAN;
  long double res1 = s21_floor(test);
  long double res2 = floor(test);

  ck_assert_ldouble_nan(res1);
  ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(floor_pos_inf_test) {
  double test = INFINITY;
  long double res1 = s21_floor(test);
  long double res2 = floor(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(floor_neg_inf_test) {
  double test = -INFINITY;
  long double res1 = s21_floor(test);
  long double res2 = floor(test);

  ck_assert_ldouble_infinite(res1);
  ck_assert_ldouble_infinite(res2);
}
END_TEST

START_TEST(floor_pos_loop_test) {
  for (double test = 1.1293; test <= 1000.0; test += 10.0452525235) {
    long double res1 = s21_floor(test);
    long double res2 = floor(test);
    ck_assert_ldouble_eq(res1, res2);
  }
}
END_TEST

START_TEST(floor_neg_loop_test) {
  for (double test = -1000.013; test <= -1.0; test += 10.0452525235) {
    long double res1 = s21_floor(test);
    long double res2 = floor(test);
    ck_assert_ldouble_eq(res1, res2);
  }
}
END_TEST

START_TEST(floor_zero_loop_test) {
  for (double test = -0.999999; test <= 1.0; test += 0.0452525235) {
    long double res1 = s21_floor(test);
    long double res2 = floor(test);
    ck_assert_ldouble_eq(res1, res2);
  }
}
END_TEST

START_TEST(floor_no_float_loop_test) {
  for (double test = -100; test <= 100; test += 1) {
    long double res1 = s21_floor(test);
    long double res2 = floor(test);
    ck_assert_ldouble_eq(res1, res2);
  }
}
END_TEST

Suite *test_floor_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("floor_test");
  /* Core test case */
  tc = tcase_create("floor_tc");

  // floor
  tcase_add_test(tc, floor_simple_test);
  tcase_add_test(tc, floor_zero_test);
  tcase_add_test(tc, floor_nan_test);
  tcase_add_test(tc, floor_pos_inf_test);
  tcase_add_test(tc, floor_neg_inf_test);
  tcase_add_test(tc, floor_pos_loop_test);
  tcase_add_test(tc, floor_neg_loop_test);
  tcase_add_test(tc, floor_zero_loop_test);
  tcase_add_test(tc, floor_no_float_loop_test);

  suite_add_tcase(s, tc);

  return s;
}
