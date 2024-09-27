#include "../s21_decimal.h"

/*
 a *  b
-a * -b =   a * b
-a *  b = -(a * b)
 a * -b = -(a * b)
*/

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clear_decimal(result);
  int overflow = 0;
  int error = 0;
  int res_sign = get_sign(value_1) ^ get_sign(value_2);
  int res_scale = get_scale(value_1) + get_scale(value_2);
  int zero = s21_is_equal_zero(value_1) || s21_is_equal_zero(value_2);
  s21_big_decimal val_d1 = {0}, val_d2 = {0}, res_d3 = {0};
  if (zero) {
    // printf("ZERO\n");
  } else {
    copy_to_big(&val_d1, value_1);
    copy_to_big(&val_d2, value_2);
    s21_big_mul_mant(val_d1, val_d2, &res_d3);
  }
  while (res_scale > 28) {
    s21_big_div_mant_int(&res_d3, 10);
    res_scale--;
  }
  set_scale(result, res_scale);
  set_big_scale(&res_d3, res_scale);
  if (res_sign) {
    set_big_sign(&res_d3);
    set_sign(result);
  }
  overflow = s21_big_check_overflow(res_d3);
  if (overflow == 1) {
    if (res_sign) {
      error = 2;
    } else {
      error = 1;
    }
  } else {
    s21_from_big_to_norm_decimal(result, res_d3);
  }
  return error;
}