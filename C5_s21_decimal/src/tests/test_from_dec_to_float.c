#include "test.h"

START_TEST(s21_dec_to_float_er00) {
  float *out = NULL;
  s21_decimal inp = {0};
  int error = s21_from_decimal_to_float(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_dec_to_float_00) {
  float out = 0.0;
  s21_decimal inp = {{258, 0, 0, 0}};

  int error = s21_from_decimal_to_float(inp, &out);
  ck_assert_float_eq(out, 258);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_01) {
  float out = 0.0;
  s21_decimal inp = {{258, 0, 0, 0}};
  set_scale(&inp, 2);
  int error = s21_from_decimal_to_float(inp, &out);
  ck_assert_float_eq(out, 2.58);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_02) {
  float out = 0.0;
  s21_decimal inp = {{258, 0, 0, 2147483648}};
  set_scale(&inp, 5);
  int error = s21_from_decimal_to_float(inp, &out);
  ck_assert_float_eq(out, -0.00258);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_03) {
  float out = 0.0;
  s21_decimal inp = {{0b010110001101110110, 0b0100101, 0b0100011010000110,
                      0}};  // = 3.3303751750691E+23
  set_scale(&inp, 15);
  int error = s21_from_decimal_to_float(inp, &out);
  ck_assert_float_eq(out, 333037517.50691);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_04) {
  float out = 0.0;
  s21_decimal inp = {{0b010110001101110110, 0b0100101, 0b0100011010000110,
                      0}};  // = 3.3303751750691E+23
  set_scale(&inp, 14);
  int error = s21_from_decimal_to_float(inp, &out);
  ck_assert_float_eq(out, 3330375175.06911158756214);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_05) {
  float out = 0.0;
  s21_decimal inp = {{0b010110001101110110, 0b0100101, 0b0100011010000110,
                      2147483648}};  // = 3.3303751750691E+23
  set_scale(&inp, 18);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = -3.3303751750691E+5;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_06) {
  float out = 0.0;
  s21_decimal inp = {{0, 0, 0, 0}};
  set_scale(&inp, 18);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = 0;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_07) {
  float out = 0.0;
  s21_decimal inp = {
      {0b110001000101001010, 0b010101000101010110, 0, 0}};  // = 370904785949002
  set_scale(&inp, 13);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = 37.0904785949002;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_08) {
  float out = 0.0;
  s21_decimal inp = {{0b110001000101001010, 0b010101000101010110, 0,
                      2147483648}};  // = 370904785949002
  set_scale(&inp, 18);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = -0.000370904785949002;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_minuszero) {
  float out = 0.0;
  s21_decimal inp = {{0, 0, 0, 2147483648}};
  set_scale(&inp, 0);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = 0;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_zero) {
  float out = 0.0;
  s21_decimal inp = {{0, 0, 0, 0}};
  set_scale(&inp, 0);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = 0;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dec_to_float_float) {
  float out = 100.0;
  s21_decimal inp = {{0, 0, 0, 0}};
  set_scale(&inp, 0);
  int error = s21_from_decimal_to_float(inp, &out);
  float res = 0.0;
  ck_assert_float_eq(out, res);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_from_decimal_to_float(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_FLOAT=-\033[0m");
  TCase *tc = tcase_create("s21_from_decimal_to_float_tc");

  tcase_add_test(tc, s21_dec_to_float_er00);
  tcase_add_test(tc, s21_dec_to_float_00);
  tcase_add_test(tc, s21_dec_to_float_01);
  tcase_add_test(tc, s21_dec_to_float_02);
  tcase_add_test(tc, s21_dec_to_float_03);
  tcase_add_test(tc, s21_dec_to_float_04);
  tcase_add_test(tc, s21_dec_to_float_05);
  tcase_add_test(tc, s21_dec_to_float_06);
  tcase_add_test(tc, s21_dec_to_float_07);
  tcase_add_test(tc, s21_dec_to_float_08);
  tcase_add_test(tc, s21_dec_to_float_minuszero);
  tcase_add_test(tc, s21_dec_to_float_zero);
  tcase_add_test(tc, s21_dec_to_float_float);

  suite_add_tcase(s, tc);
  return s;
}