#include "test.h"

START_TEST(s21_decimal_comp_0) {
  printf("Start compare tests.\n");
  s21_decimal s_decimal_1 = {0};
  s21_decimal s_decimal_2 = {0};
  // 0 > 0 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 0 >= 0 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 0 == 0 = true (1)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 0 < 0 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 0 <= 0 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 0 != 0 = false (0)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 1);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 0);
}
END_TEST

START_TEST(s21_decimal_comp_1) {
  // 200 / 10^2 = 2
  s21_decimal s_decimal_1 = {{200, 0, 0, 0}};
  set_scale(&s_decimal_1, 2);
  // 2
  s21_decimal s_decimal_2 = {{2, 0, 0, 0}};
  // 2 > 2 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 2 >= 2 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 2 == 2 = true (1)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 2 < 2 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 2 <= 2 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 2 != 2 = false (0)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 1);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 0);
}
END_TEST

START_TEST(s21_decimal_comp_2) {
  // 100
  s21_decimal s_decimal_1 = {{100, 0, 0, 0}};
  // 50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  // 100 > 50 = true (1)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 100 >= 50 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 100 == 50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 100 < 50 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 100 <= 50 = false (0)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 100 != 50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 0);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_3) {
  // -100
  s21_decimal s_decimal_1 = {{100, 0, 0, 0}};
  set_sign(&s_decimal_1);
  // -50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  set_sign(&s_decimal_2);
  // -100 > -50 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // -100 >= -50 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // -100 == -50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // -100 < -50 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // -100 <= -50 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // -100 != -50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_4) {
  // 79228162514264337593543950335 (MAX_DECIMAL)
  s21_decimal s_decimal_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  // 1
  s21_decimal s_decimal_2 = {{1, 0, 0, 0}};
  // MAX_DECIMAL > 1 = true (1)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // MAX_DECIMAL >= 1 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // MAX_DECIMAL == 1 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // MAX_DECIMAL < 1 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // MAX_DECIMAL <= 1 = false (0)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // MAX_DECIMAL != 1 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 0);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_5) {
  // 7.9228162514264337593543950335
  s21_decimal s_decimal_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  set_scale(&s_decimal_1, 28);
  // 8
  s21_decimal s_decimal_2 = {{8, 0, 0, 0}};
  // 7.9 > 8 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 7.9 >= 8 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 7.9 == 8 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 7.9 < 8 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 7.9 <= 8 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 7.9 != 8 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_6) {
  // 0
  s21_decimal s_decimal_1 = {0};
  // -0
  s21_decimal s_decimal_2 = {0};
  set_sign(&s_decimal_2);
  // 0 > -0 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 0 >= -0 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 0 == -0 = true (1)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 0 < -0 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 0 <= -0 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 0 != -0 = false (0)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 1);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 0);
}
END_TEST

START_TEST(s21_decimal_comp_7) {
  // -0.5
  s21_decimal s_decimal_1 = {{5000, 0, 0, 0}};
  set_scale(&s_decimal_1, 4);
  set_sign(&s_decimal_1);
  // -5
  s21_decimal s_decimal_2 = {{500, 0, 0, 0}};
  set_scale(&s_decimal_2, 2);
  set_sign(&s_decimal_2);
  // -0.5 > -5 = true (1)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // -0.5 >= -5 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // -0.5 == -5 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // -0.5 < -5 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // -0.5 <= -5 = false (0)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // -0.5 != -5 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 0);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_8) {
  // -18446744073709556616
  s21_decimal s_decimal_1 = {{5000, 0, 1, 0}};
  set_sign(&s_decimal_1);
  // -50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  set_sign(&s_decimal_2);
  // -18446744073709556616 > -50 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // -18446744073709556616 >= -50 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // -18446744073709556616 == -50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // -18446744073709556616 < -50 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // -18446744073709556616 <= -50 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // -18446744073709556616 != -50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_9) {
  // -4294972296
  s21_decimal s_decimal_1 = {{5000, 1, 0, 0}};
  set_sign(&s_decimal_1);
  // -50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  set_sign(&s_decimal_2);
  // -4294972296 > -50 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // -4294972296 >= -50 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // -4294972296 == -50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // -4294972296 < -50 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // -4294972296 <= -50 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // -4294972296 != -50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_10) {
  // 4294972296
  s21_decimal s_decimal_1 = {{5000, 1, 0, 0}};
  // 50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  // 4294972296 > 50 = true (1)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 4294972296 >= 50 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 4294972296 == 50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 4294972296 < 50 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 4294972296 <= 50 = false (0)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 4294972296 != 50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 0);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_11) {
  // -4294972296
  s21_decimal s_decimal_1 = {{50, 1, 0, 0}};
  set_sign(&s_decimal_1);
  // 50
  s21_decimal s_decimal_2 = {{50, 0, 0, 0}};
  // -4294972296 > 50 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // -4294972296 >= 50 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // -4294972296 == 50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // -4294972296 < 50 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // -4294972296 <= 50 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // -4294972296 != 50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_12) {
  // 4294972296
  s21_decimal s_decimal_1 = {{50, 1, 0, 0}};
  // -50
  s21_decimal s_decimal_2 = {{50, 1, 0, 0}};
  set_sign(&s_decimal_2);
  // 4294972296 > -50 = true (1)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 4294972296 >= -50 = true (1)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 4294972296 == -50 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 4294972296 < -50 = false (0)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 4294972296 <= -50 = false (0)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 4294972296 != -50 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(res2, 1);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 0);
  ck_assert_int_eq(res5, 0);
  ck_assert_int_eq(res6, 1);
}
END_TEST

START_TEST(s21_decimal_comp_13) {
  // 50
  s21_decimal s_decimal_1 = {{50, 0, 0, 0}};
  // 4294972296
  s21_decimal s_decimal_2 = {{5000, 1, 0, 0}};
  // 50 > 4294972296 = false (0)
  int res1 = s21_is_greater(s_decimal_1, s_decimal_2);
  // 50 >= 4294972296 = false (0)
  int res2 = s21_is_greater_or_equal(s_decimal_1, s_decimal_2);
  // 50 == 4294972296 = false (0)
  int res3 = s21_is_equal(s_decimal_1, s_decimal_2);
  // 50 < 4294972296 = true (1)
  int res4 = s21_is_less(s_decimal_1, s_decimal_2);
  // 50 <= 4294972296 = true (1)
  int res5 = s21_is_less_or_equal(s_decimal_1, s_decimal_2);
  // 50 != 4294972296 = true (1)
  int res6 = s21_is_not_equal(s_decimal_1, s_decimal_2);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(res3, 0);
  ck_assert_int_eq(res4, 1);
  ck_assert_int_eq(res5, 1);
  ck_assert_int_eq(res6, 1);
}
END_TEST

Suite *test_comp_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[45m-=S21_COMPARISION_DECIMALS=-\033[0m");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, s21_decimal_comp_0);
  tcase_add_test(tc, s21_decimal_comp_1);
  tcase_add_test(tc, s21_decimal_comp_2);
  tcase_add_test(tc, s21_decimal_comp_3);
  tcase_add_test(tc, s21_decimal_comp_4);
  tcase_add_test(tc, s21_decimal_comp_5);
  tcase_add_test(tc, s21_decimal_comp_6);
  tcase_add_test(tc, s21_decimal_comp_7);
  tcase_add_test(tc, s21_decimal_comp_8);
  tcase_add_test(tc, s21_decimal_comp_9);
  tcase_add_test(tc, s21_decimal_comp_10);
  tcase_add_test(tc, s21_decimal_comp_11);
  tcase_add_test(tc, s21_decimal_comp_12);
  tcase_add_test(tc, s21_decimal_comp_13);

  suite_add_tcase(s, tc);

  return s;
}