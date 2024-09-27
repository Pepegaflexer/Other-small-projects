#include "test.h"

START_TEST(s21_add_test_1) {
  printf("Start add tests.\n");
  int x1 = 0, x2 = 0, x3 = 0, res;
  s21_decimal a1, a2, a3;
  for (x1 = -50; x1 <= 50; x1++) {
    for (x2 = -50; x2 <= -50; x2++) {
      // x1 = 11;
      // x2 = -10;
      // printf("x1 = %d, x2 = %d, x1+x2 = %d\n", x1, x2, x1 + x2);
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_add(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 + x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
  for (x1 = -10050; x1 <= -9950; x1++) {
    for (x2 = -10050; x2 <= -9950; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_add(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 + x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
  for (x1 = 9950; x1 <= 10050; x1++) {
    for (x2 = 9950; x2 <= 10050; x2++) {
      s21_from_int_to_decimal(x1, &a1);
      s21_from_int_to_decimal(x2, &a2);
      res = s21_add(a1, a2, &a3);
      s21_from_decimal_to_int(a3, &x3);
      ck_assert_int_eq(x1 + x2, x3);
      ck_assert_int_eq(res, 0);
    }
  }
}
END_TEST

START_TEST(minus_overflow_test) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};

  set_bit(&a, 95);
  set_bit(&a, 94);
  set_bit(&b, 95);
  set_bit(&b, 94);
  set_sign(&a);
  set_sign(&b);
  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, S21_N_INF);
}
END_TEST

START_TEST(overflow_test) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};

  set_bit(&a, 95);
  set_bit(&a, 94);
  set_bit(&b, 95);
  set_bit(&b, 94);
  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, S21_INF);
}
END_TEST

START_TEST(max_plus_one) {
  s21_decimal a = {0};
  a.bits[0] = 4294967295;
  a.bits[1] = 4294967295;
  a.bits[2] = 4294967295;
  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_decimal res = {0};

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, S21_INF);
}
END_TEST

START_TEST(before_max_plus_one) {
  s21_decimal a = {0};
  a.bits[0] = 4294967294;
  a.bits[1] = 4294967295;
  a.bits[2] = 4294967295;
  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_decimal res = {0};

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, NORM);
}
END_TEST

START_TEST(minus_max_minus_one) {
  s21_decimal a = {0};
  a.bits[0] = 4294967295;
  a.bits[1] = 4294967295;
  a.bits[2] = 4294967295;
  set_sign(&a);
  s21_decimal b = {0};
  b.bits[0] = 1;
  set_sign(&b);
  s21_decimal res = {0};

  int code = s21_add(a, b, &res);

  ck_assert_int_eq(code, S21_N_INF);
}
END_TEST

START_TEST(minus_before_max_minus_one) {
  s21_decimal a = {0};
  a.bits[0] = 4294967294;
  a.bits[1] = 4294967295;
  a.bits[2] = 4294967295;
  set_sign(&a);
  s21_decimal b = {0};
  b.bits[0] = 1;
  set_sign(&b);
  s21_decimal res = {0};
  s21_decimal res_control = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&res_control);

  int code = s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, res_control), 1);
  ck_assert_int_eq(code, NORM);
}
END_TEST

START_TEST(little_plus_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{5000, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{0, 0, 0, 0}};
  int res = s21_add(value_2, value_1, &result);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(little_plus_not_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4999, 0, 0, 0}};
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  int res = s21_add(value_2, value_1, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(little_minus_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&value_1);
  s21_decimal value_2 = {{5000, 0, 0, 0}};
  set_sign(&value_2);
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{0, 0, 0, 0}};
  int res = s21_add(value_2, value_1, &result);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

START_TEST(little_minus_not_overflow) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&value_1);
  s21_decimal value_2 = {{4999, 0, 0, 0}};
  set_sign(&value_2);
  set_scale(&value_2, 4);
  s21_decimal result = {0};
  s21_decimal result_control = {{4294967295, 4294967295, 4294967295, 0}};
  set_sign(&result_control);
  int res = s21_add(value_2, value_1, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, result_control), 1);
}
END_TEST

Suite *test_add_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[45m-=S21_ADD=-\033[0m");
  /* Core test case */
  tc = tcase_create("add_tc");

  // abs
  tcase_add_test(tc, s21_add_test_1);
  tcase_add_test(tc, minus_overflow_test);
  tcase_add_test(tc, overflow_test);
  tcase_add_test(tc, max_plus_one);
  tcase_add_test(tc, before_max_plus_one);
  tcase_add_test(tc, minus_max_minus_one);
  tcase_add_test(tc, minus_before_max_minus_one);
  tcase_add_test(tc, little_plus_overflow);
  tcase_add_test(tc, little_plus_not_overflow);
  tcase_add_test(tc, little_minus_overflow);
  tcase_add_test(tc, little_minus_not_overflow);

  suite_add_tcase(s, tc);

  return s;
}
