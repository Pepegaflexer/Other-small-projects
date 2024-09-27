#include "test.h"

START_TEST(s21_sub_test_1) {
  printf("Start sub tests.\n");
  int x1 = 0, x2 = 0, x3 = 0, res;
  s21_decimal a1, a2, a3;
  for (x1 = -50; x1 <= 50; x1++) {
    for (x2 = -50; x2 <= 50; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_sub(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 - x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
  for (x1 = -10050; x1 <= -9950; x1++) {
    for (x2 = -10050; x2 <= -9950; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_sub(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 - x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
  for (x1 = 9950; x1 <= 10050; x1++) {
    for (x2 = 9950; x2 <= 10050; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_sub(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 - x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{0, 0, 4294967295, 0}};
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{0, 0, 4294967295, 0}};
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 0, 0}};
  set_sign(&result_control);
  int res = s21_sub(value_2, value_1, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967287, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{5000, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967294, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4999, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967294, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  // show_decimal(result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4000, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(max_minus_min) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(plus_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{5000, 0, 0, 0}};
  set_scale(&value_2, 4);
  set_sign(&value_2);
  s21_decimal result = {0};
  s21_decimal result_control = {{0, 0, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(plus_no_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4999, 0, 0, 0}};
  set_scale(&value_2, 4);
  set_sign(&value_2);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(minus_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&value_1);
  s21_decimal value_2 = {{5000, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{0, 0, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(minus_no_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&value_1);
  s21_decimal value_2 = {{4999, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&result_control);
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

Suite *test_sub_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[45m-=S21_SUB=-\033[0m");
  /* Core test case */
  tc = tcase_create("sub_tc");

  tcase_add_test(tc, s21_sub_test_1);
  tcase_add_test(tc, s21_sub_test_2);
  tcase_add_test(tc, s21_sub_test_3);
  tcase_add_test(tc, s21_sub_test_4);
  tcase_add_test(tc, s21_sub_test_5);
  tcase_add_test(tc, s21_sub_test_6);
  tcase_add_test(tc, s21_sub_test_7);
  tcase_add_test(tc, max_minus_min);
  tcase_add_test(tc, plus_overflow);
  tcase_add_test(tc, plus_no_overflow);
  tcase_add_test(tc, minus_overflow);
  tcase_add_test(tc, minus_no_overflow);

  suite_add_tcase(s, tc);

  return s;
}