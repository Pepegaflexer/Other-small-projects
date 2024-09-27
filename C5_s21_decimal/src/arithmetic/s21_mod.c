#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clear_decimal(result);
  int overflow = 0;
  int error = 0;
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  int count = 0;
  s21_big_decimal val_d1 = {0}, val_d2 = {0}, res_d3 = {0};
  s21_big_decimal tmp_d = {0};
  copy_to_big(&val_d1, value_1);
  copy_to_big(&val_d2, value_2);
  big_normalize(&val_d1, &val_d2);
  s21_big_div_mant(val_d1, val_d2, &tmp_d);
  overflow = s21_big_check_overflow(tmp_d);
  int second_zero = s21_is_equal_zero(value_2);
  int zero = s21_is_big_equal_zero(tmp_d);
  if (second_zero) {
    error = 3;
  } else if (overflow) {
    if (sign1 ^ sign2) {
      error = 2;
    } else {
      error = 1;
    }
  } else if (zero) {
    *result = value_1;
  } else {
    int max_bit = find_big_max_bit(val_d1);
    int scale = get_big_scale(val_d1);
    s21_big_mod_mant(val_d1, val_d2, &res_d3);
    if (max_bit > 95) {
      while (find_big_max_bit(val_d1) > 95) {
        count++;
        s21_big_div_mant_int(&val_d1, 10);
      }
      s21_big_round(&res_d3, count);
      scale -= count;
    }
    set_big_scale(&res_d3, scale);
    if (sign1) {
      set_big_sign(&res_d3);
    }
    s21_from_big_to_norm_decimal(result, res_d3);
  }
  return error;
}