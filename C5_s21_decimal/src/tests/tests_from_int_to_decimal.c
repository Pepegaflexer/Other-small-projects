#include "test.h"

START_TEST(s21_int_er00) {
  int inp = 1;
  s21_decimal *out = NULL;
  int error = s21_from_int_to_decimal(inp, out);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_int_zero) {
  int inp = 0;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_0) {
  int inp = -321;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{321, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_1) {
  int inp = 321;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{321, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_2) {
  int inp = 788954325;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{788954325, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_3) {
  int inp = -788954325;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{788954325, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_4) {
  int inp = 1076;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{1076, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_5) {
  int inp = -1076;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{1076, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_max) {
  int inp = 2147483647;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{2147483647, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_int_min) {
  int inp = -2147483648;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{2147483648, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_from_int_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_INT_TO_DECIMAL=-\033[0m");
  TCase *tc = tcase_create("s21_from_int_to_decimal_tc");

  tcase_add_test(tc, s21_int_er00);
  tcase_add_test(tc, s21_int_zero);
  tcase_add_test(tc, s21_int_0);
  tcase_add_test(tc, s21_int_1);
  tcase_add_test(tc, s21_int_2);
  tcase_add_test(tc, s21_int_3);
  tcase_add_test(tc, s21_int_4);
  tcase_add_test(tc, s21_int_5);
  tcase_add_test(tc, s21_int_max);
  tcase_add_test(tc, s21_int_min);

  suite_add_tcase(s, tc);
  return s;
}