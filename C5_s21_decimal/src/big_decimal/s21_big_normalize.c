#include "../s21_decimal.h"

int big_normalize(s21_big_decimal *d1, s21_big_decimal *d2) {
  int scale_d1 = get_big_scale(*d1);
  int scale_d2 = get_big_scale(*d2);
  int sign_d1 = get_big_sign(*d1);
  int sign_d2 = get_big_sign(*d2);
  s21_big_decimal tmp_d = {0};
  s21_big_decimal dec_10 = {0};
  dec_10.bits[0] = 10;
  if (scale_d1 > scale_d2) {
    while (scale_d1 != scale_d2 && scale_d2 < 28) {
      scale_d2++;
      s21_big_mul_mant(*d2, dec_10, &tmp_d);
      *d2 = tmp_d;
    }
  } else if (scale_d2 > scale_d1) {
    while (scale_d2 != scale_d1 && scale_d1 < 28) {
      scale_d1++;
      s21_big_mul_mant(*d1, dec_10, &tmp_d);
      *d1 = tmp_d;
    }
  }
  set_big_scale(d1, scale_d1);
  set_big_scale(d2, scale_d2);

  if (sign_d1) {
    set_big_sign(d1);
  }
  if (sign_d2) {
    set_big_sign(d2);
  }
  return 0;
}