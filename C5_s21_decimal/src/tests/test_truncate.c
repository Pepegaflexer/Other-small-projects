#include "test.h"

START_TEST(s21_truncate_000) {
  s21_decimal inp = {{0x000004D2, 0, 0, 0x80030000}};
  s21_decimal *out = NULL;
  int error = s21_truncate(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_truncate_001) {
  s21_decimal inp = {{0x000004D2, 0, 0, 0x80030000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x00000001, 0, 0, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_truncate_002) {
  s21_decimal inp = {{0x000004D2, 0, 0, 0x00030000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x00000001, 0, 0, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_truncate_003) {
  s21_decimal inp = {{0x0001E29A, 0x000A0128, 0, 0x00040000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x90CB296A, 0x00000041, 0, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_truncate_004) {
  s21_decimal inp = {{0x0001E29A, 0x000A0128, 0, 0x00040000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x90CB296A, 0x00000041, 0, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_truncate_005) {
  s21_decimal inp = {{0x0001E29A, 0x000A0128, 0x0009FCF3, 0x800A0000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x8A32534A, 0x00044A33, 0, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_truncate_006) {
  s21_decimal inp = {{0x000004D3, 0x0000199C, 0x00001995, 0x00110000}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_truncate(inp, &out);
  s21_decimal res = {{0x00126F0D, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_truncate_suite(void) {
  Suite *s = suite_create("\033[45m-=S21_TRUNCATE=-\033[0m");
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, s21_truncate_000);
  tcase_add_test(tc, s21_truncate_001);
  tcase_add_test(tc, s21_truncate_002);
  tcase_add_test(tc, s21_truncate_003);
  tcase_add_test(tc, s21_truncate_004);
  tcase_add_test(tc, s21_truncate_005);
  tcase_add_test(tc, s21_truncate_006);

  suite_add_tcase(s, tc);
  return s;
}