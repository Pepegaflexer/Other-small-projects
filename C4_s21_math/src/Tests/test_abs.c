#include "test.h"

/*-----ABS-----*/
START_TEST(abs_negative_test) {
  int test = -50;
  int res1 = s21_abs(test);
  int res2 = abs(test);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(abs_positive_test) {
  int test = 650;
  int res1 = s21_abs(test);
  int res2 = abs(test);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(abs_intmin_test) {
  int test = -2147483648;
  int res1 = s21_abs(test);
  int res2 = abs(test);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(abs_loop_test) {
  for (int test = -2147483600; test <= -2147483600; test += 100) {
    int res1 = s21_abs(test);
    int res2 = abs(test);
    ck_assert_int_eq(res1, res2);
  }
}
END_TEST

Suite *test_abs_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("abs_test");
  /* Core test case */
  tc = tcase_create("abs_tc");

  // abs
  tcase_add_test(tc, abs_negative_test);
  tcase_add_test(tc, abs_positive_test);
  tcase_add_test(tc, abs_intmin_test);
  tcase_add_test(tc, abs_loop_test);

  suite_add_tcase(s, tc);

  return s;
}
