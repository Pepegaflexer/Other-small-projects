#include "../s21_decimal.h"

/*
 a /  b
-a / -b =   a / b
-a /  b = -(a / b)
 a / -b = -(a / b)
*/

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clear_decimal(result);
  int overflow = 0;
  int error = 0;
  int res_sign = get_sign(value_1) ^ get_sign(value_2);
  int res_scale = get_scale(value_1) - get_scale(value_2);
  int zero = s21_is_equal_zero(value_2);

  s21_big_decimal val_d1 = {0}, val_d2 = {0}, res_d3 = {0};
  s21_big_decimal rem_d = {0};
  s21_big_decimal tmp_d = {0};
  s21_big_decimal fin_res_d = {0};
  s21_big_decimal ten_d = {{10, 0, 0, 0, 0, 0, 0}};

  if (zero) {
    error = 3;
  } else {
    copy_to_big(&val_d1, value_1);
    copy_to_big(&val_d2, value_2);
    s21_big_div_mant(val_d1, val_d2, &res_d3);
    tmp_d = fin_res_d;
    s21_big_add_mant(res_d3, tmp_d, &fin_res_d);
    s21_big_mod_mant(val_d1, val_d2, &rem_d);
    while (is_not_empty_big_decimal(rem_d) && res_scale < 28) {
      s21_big_mul_mant(rem_d, ten_d, &tmp_d);
      s21_big_mul_mant_int(&fin_res_d, 10);
      s21_big_div_mant(tmp_d, val_d2, &res_d3);
      s21_big_mod_mant(tmp_d, val_d2, &rem_d);
      tmp_d = fin_res_d;
      s21_big_add_mant(tmp_d, res_d3, &fin_res_d);
      res_scale++;
    }
    while (res_scale < 0) {
      s21_big_mul_mant_int(&fin_res_d, 10);
      res_scale++;
    }
    set_big_scale(&fin_res_d, res_scale);
    overflow = s21_big_check_overflow(fin_res_d);
    if (overflow) {
      if (res_sign || overflow == 2) {
        error = 2;
      } else {
        error = 1;
      }
    } else {
      s21_from_big_to_norm_decimal(result, fin_res_d);
    }
    if (res_sign) {
      set_sign(result);
    }
  }
  return error;
}