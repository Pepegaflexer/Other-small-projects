#include "test.h"

START_TEST(s21_dec_to_int_er00) {
  int *out = NULL;
  s21_decimal inp = {{1, 0, 0, 0}};
  int error = s21_from_decimal_to_int(inp, out);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_dec_to_int_er01) {
  int out = 0;
  s21_decimal inp = {{0, 1, 0, 0}};
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_er02) {
  int out = 0;
  s21_decimal inp = {{0, 0, 1, 0}};
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_er03) {
  int out = 0;
  s21_decimal inp = {{0, 0, 1, 0}};
  set_scale(&inp, 5);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_er04) {
  int out = 0;
  s21_decimal inp = {{0, 0, 1, 0}};
  set_scale(&inp, 5);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_00) {
  int out = 0;
  s21_decimal inp = {{1, 0, 0, 0}};
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 1);
}
END_TEST

START_TEST(s21_dec_to_int_01) {
  int out = 0;
  s21_decimal inp = {{10000, 0, 0, 0}};
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 10000);
}
END_TEST

START_TEST(s21_dec_to_int_02) {
  int out = 0;
  s21_decimal inp = {{100, 0, 0, 0}};
  set_scale(&inp, 2);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 1);
}
END_TEST

START_TEST(s21_dec_to_int_03) {
  int out = 0;
  s21_decimal inp = {{1356, 0, 0, 0}};
  set_scale(&inp, 3);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 1);
}
END_TEST

START_TEST(s21_dec_to_int_04) {
  int out = 0;
  s21_decimal inp = {{1356, 0, 0, 0}};
  set_scale(&inp, 2);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 13);
}
END_TEST

START_TEST(s21_dec_to_int_05) {
  int out = 0;
  s21_decimal inp = {{1356, 0, 0, 2147483648}};
  set_scale(&inp, 1);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, -135);
}
END_TEST

START_TEST(s21_dec_to_int_06) {
  int out = 0;
  s21_decimal inp = {{0, 1, 0, 0}};  // = 4294967296
  set_scale(&inp, 2);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 42949672);
}
END_TEST

START_TEST(s21_dec_to_int_07) {
  int out = 0;
  s21_decimal inp = {{0, 1, 0, 0}};  // = 4294967296
  set_scale(&inp, 6);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 4294);
}
END_TEST

START_TEST(s21_dec_to_int_08) {
  int out = 0;
  s21_decimal inp = {
      {0b11011010010101111001011001100, 0, 0, 2147483648}};  // = 457896652
  set_scale(&inp, 8);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, -4);
}
END_TEST

START_TEST(s21_dec_to_int_09) {
  int out = 0;
  s21_decimal inp = {
      {0b11011010010101111001011001100, 0, 0, 0}};  // = 457896652
  set_scale(&inp, 0);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 457896652);
}
END_TEST

START_TEST(s21_dec_to_int_10) {
  int out = 0;
  s21_decimal inp = {
      {0b10, 0b1110101101101100110000011110000, 0, 0}};  // = 7899546562
  set_scale(&inp, 0);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_11) {
  int out = 0;
  s21_decimal inp = {{0b01010110, 0b01001101110101, 0b010100010000101001,
                      0}};  // = 1530803056978200000000000
  set_scale(&inp, 18);
  int error = s21_from_decimal_to_int(inp, &out);
  // show_decimal(inp);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 1530803);
}
END_TEST

START_TEST(s21_dec_to_int_12) {
  int out = 0;
  s21_decimal inp = {{0b01010110, 0b01001101110101, 0b010100010000101001,
                      2147483648}};  // 1530803056978200000000000
  set_scale(&inp, 24);
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, -1);
}
END_TEST

START_TEST(s21_dec_to_int_max) {
  int out = 0;
  s21_decimal inp = {{2147483647, 0, 0, 0}};  // 1530803056978200000000000
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, 2147483647);
}
END_TEST

START_TEST(s21_dec_to_int_min) {
  int out = 0;
  s21_decimal inp = {
      {2147483648, 0, 0, 2147483648}};  // 1530803056978200000000000
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, -2147483648);
}
END_TEST

START_TEST(s21_dec_to_int_min_minus_1) {
  int out = 0;
  s21_decimal inp = {
      {2147483647, 0, 0, 2147483648}};  // 1530803056978200000000000
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(out, -2147483647);
}
END_TEST

START_TEST(s21_dec_to_int_max_error) {
  int out = 0;
  s21_decimal inp = {{2147483648, 0, 0, 0}};  // 1530803056978200000000000
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

START_TEST(s21_dec_to_int_min_error) {
  int out = 0;
  s21_decimal inp = {
      {2147483649, 0, 0, 2147483648}};  // 1530803056978200000000000
  int error = s21_from_decimal_to_int(inp, &out);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(out, 0);
}
END_TEST

Suite *test_from_decimal_to_int(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_INT=-\033[0m");
  TCase *tc = tcase_create("s21_from_decimal_to_int_tc");

  tcase_add_test(tc, s21_dec_to_int_er00);
  tcase_add_test(tc, s21_dec_to_int_er01);
  tcase_add_test(tc, s21_dec_to_int_er02);
  tcase_add_test(tc, s21_dec_to_int_er03);
  tcase_add_test(tc, s21_dec_to_int_er04);
  tcase_add_test(tc, s21_dec_to_int_00);
  tcase_add_test(tc, s21_dec_to_int_01);
  tcase_add_test(tc, s21_dec_to_int_02);
  tcase_add_test(tc, s21_dec_to_int_03);
  tcase_add_test(tc, s21_dec_to_int_04);
  tcase_add_test(tc, s21_dec_to_int_05);
  tcase_add_test(tc, s21_dec_to_int_06);
  tcase_add_test(tc, s21_dec_to_int_07);
  tcase_add_test(tc, s21_dec_to_int_08);
  tcase_add_test(tc, s21_dec_to_int_09);
  tcase_add_test(tc, s21_dec_to_int_10);
  tcase_add_test(tc, s21_dec_to_int_11);
  tcase_add_test(tc, s21_dec_to_int_12);
  tcase_add_test(tc, s21_dec_to_int_max);
  tcase_add_test(tc, s21_dec_to_int_min);
  tcase_add_test(tc, s21_dec_to_int_min_minus_1);
  tcase_add_test(tc, s21_dec_to_int_max_error);
  tcase_add_test(tc, s21_dec_to_int_min_error);
  suite_add_tcase(s, tc);
  return s;
}