#include "test.h"

START_TEST(s21_floor_error_00) {
  s21_decimal inp = {{123, 3434, 123, 12341}};
  s21_decimal *out = NULL;
  int error = s21_floor(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_floor_00) {
  s21_decimal inp = {{123, 0, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_floor(inp, &out);
  s21_decimal res = {{123, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_01) {
  s21_decimal inp = {{123, 0, 0, 0}};
  set_scale(&inp, 2);
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_floor(inp, &out);
  s21_decimal res = {{1, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_02) {
  s21_decimal inp = {{123, 0, 0, 2147483648}};
  set_scale(&inp, 1);
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_floor(inp, &out);
  s21_decimal res = {{13, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_03) {
  s21_decimal inp = {{200, 0, 0, 2147483648}};
  set_scale(&inp, 2);
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_floor(inp, &out);
  s21_decimal res = {{2, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_floor_suite(void) {
  Suite *s = suite_create("\033[45m-=S21_FLOOR=-\033[0m");
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, s21_floor_error_00);
  tcase_add_test(tc, s21_floor_00);
  tcase_add_test(tc, s21_floor_01);
  tcase_add_test(tc, s21_floor_02);
  tcase_add_test(tc, s21_floor_03);
  suite_add_tcase(s, tc);
  return s;
}