#include "test.h"

START_TEST(s21_div_test_1) {
  printf("Start div tests.\n");
  int x1 = 0, x2 = 0, res;
  float x3;
  s21_decimal a1, a2, a3;
  for (x1 = -5; x1 <= 5; x1++) {
    for (x2 = -5; x2 <= 5; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_div(a1, a2, &a3);
      s21_from_decimal_to_float(a3, &x3);
      if (x2 != 0) {
        ck_assert_float_eq_tol((float)x1 / x2, x3, 1e-6);
        ck_assert_int_eq(res, 0);
      } else {
        ck_assert_int_eq(res, 3);
      }
    }
  }
  for (x1 = -12345; x1 <= -12340; x1++) {
    for (x2 = -12345; x2 <= -12340; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_div(a1, a2, &a3);
      s21_from_decimal_to_float(a3, &x3);
      ck_assert_float_eq_tol((float)x1 / x2, x3, 1e-6);
      ck_assert_int_eq(res, 0);
    }
  }
  for (x1 = 54321; x1 <= 54326; x1++) {
    for (x2 = 54321; x2 <= 54326; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_div(a1, a2, &a3);
      s21_from_decimal_to_float(a3, &x3);
      ck_assert_float_eq_tol((float)x1 / x2, x3, 1e-6);
      ck_assert_int_eq(res, 0);
    }
  }
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {0};
  s21_decimal result_control = {{0x10000000, 0x3E250261, 0x204FCE5E, 0}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {0};
  s21_decimal result_control = {{1, 0, 0, 0}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  set_scale(&value_1, 27);
  s21_decimal value_2 = {{100, 0, 0, 0}};
  s21_decimal result = {0};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 5);
  s21_decimal result = {0};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {0};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *test_div_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[45m-=S21_DIV=-\033[0m");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, s21_div_test_1);
  tcase_add_test(tc, s21_div_test_2);
  tcase_add_test(tc, s21_div_test_3);
  tcase_add_test(tc, s21_div_test_4);
  tcase_add_test(tc, s21_div_test_5);
  tcase_add_test(tc, s21_div_test_6);

  suite_add_tcase(s, tc);

  return s;
}
