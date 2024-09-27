#include "../s21_decimal.h"

/*
 a -  b
-a - -b =   b - a
-a -  b = -(b + a)
 a - -b =   a + b
*/

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clear_decimal(result);
  int error = 0;
  int overflow = 0;
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  s21_big_decimal val_d1 = {0}, val_d2 = {0}, res_d3 = {0};
  copy_to_big(&val_d1, value_1);
  copy_to_big(&val_d2, value_2);
  big_normalize(&val_d1, &val_d2);
  if (!(sign1 ^ sign2)) {  // both signs are equal
    if (sign1) {           // both are minus
      s21_big_sub_mant(val_d2, val_d1, &res_d3);
    } else {  // both are plus
      s21_big_sub_mant(val_d1, val_d2, &res_d3);
    }
  } else {
    if (sign1 && !sign2) {  // first is minus
      s21_big_add_mant(val_d1, val_d2, &res_d3);
      set_big_sign(&res_d3);
    } else {  // second is minus
      s21_big_add_mant(val_d1, val_d2, &res_d3);
    }
  }
  set_big_scale(&res_d3, get_big_scale(val_d1));
  overflow = s21_big_check_overflow(res_d3);
  if (overflow) {
    if (!sign1 && sign2) {
      // +++ OVERFLOW
      error = 1;
    } else if (sign1 && !sign2) {
      // --- OVERFLOW
      error = 2;
    }
  } else {
    // NO OVERFLOW
    s21_from_big_to_norm_decimal(result, res_d3);
  }
  return error;
}