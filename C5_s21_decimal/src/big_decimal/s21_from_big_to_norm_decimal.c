#include "../s21_decimal.h"

int s21_from_big_to_norm_decimal(s21_decimal *dst, s21_big_decimal src) {
  int sign = get_big_sign(src);
  int scale = get_big_scale(src);

  s21_big_decimal src_d = src;
  s21_big_decimal tmp_d = src;
  s21_big_decimal res_d = src;
  s21_big_decimal rem_d = {0};
  s21_big_decimal one_d = {{1, 0, 0, 0}};
  s21_big_decimal ten_d = {{10, 0, 0, 0}};

  while (find_big_max_bit(src_d) > 95 && scale > 0) {
    s21_big_div_mant(src_d, ten_d, &res_d);
    s21_big_mod_mant(src_d, ten_d, &rem_d);
    src_d = res_d;
    scale--;
  }
  if (rem_d.bits[0] > ten_d.bits[0] >> 1) {
    tmp_d = res_d;
    s21_big_add_mant(tmp_d, one_d, &res_d);
  } else if (rem_d.bits[0] == ten_d.bits[0] >> 1) {
    if (get_big_bit(res_d, 0) == 1) {
      tmp_d = res_d;
      s21_big_add_mant(tmp_d, one_d, &res_d);
    }
  }

  dst->bits[0] = res_d.bits[0];
  dst->bits[1] = res_d.bits[1];
  dst->bits[2] = res_d.bits[2];
  set_scale(dst, scale);
  if (sign) {
    set_sign(dst);
  }
  return 0;
}