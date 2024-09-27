#include "test.h"

START_TEST(s21_round_error_00) {
  s21_decimal inp = {{123, 3434, 123, 12341}};
  s21_decimal *out = NULL;
  int error = s21_round(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_round_00) {
  s21_decimal inp = {{123, 0, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_round(inp, &out);
  s21_decimal res = {{123, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_01) {
  s21_decimal inp = {{123, 0, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  set_scale(&inp, 1);
  int error = s21_round(inp, &out);
  s21_decimal res = {{12, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_02) {
  s21_decimal inp = {{126, 0, 0, 2147483648}};
  s21_decimal out = {{0, 123, 123, 1123}};
  set_scale(&inp, 1);
  int error = s21_round(inp, &out);
  s21_decimal res = {{13, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_03) {
  s21_decimal inp = {{0x0001E29A, 0x0006F706, 0x0000B256, 0x80070000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_round(inp, &out);
  s21_decimal res = {{0xBD223EEF, 0x012B32B3, 0, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_04) {
  s21_decimal inp = {{0x0001E29A, 0x0006F706, 0x0000B256, 0x00070000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_round(inp, &out);
  s21_decimal res = {{0xBD223EEF, 0x012B32B3, 0, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_05) {
  s21_decimal inp = {{0x0001E29A, 0x00000313, 0, 0x00070000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_round(inp, &out);
  s21_decimal res = {{0x0005285E, 0, 0, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_06) {
  s21_decimal inp = {{0x0001E29A, 0x000A0128, 0, 0x80040000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_round(inp, &out);
  s21_decimal res = {{0x90CB296B, 0x00000041, 0, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_round_suite(void) {
  Suite *s = suite_create("\033[45m-=S21_ROUND=-\033[0m");
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, s21_round_error_00);
  tcase_add_test(tc, s21_round_00);
  tcase_add_test(tc, s21_round_01);
  tcase_add_test(tc, s21_round_02);
  tcase_add_test(tc, s21_round_03);
  tcase_add_test(tc, s21_round_04);
  tcase_add_test(tc, s21_round_05);
  tcase_add_test(tc, s21_round_06);
  suite_add_tcase(s, tc);
  return s;
}