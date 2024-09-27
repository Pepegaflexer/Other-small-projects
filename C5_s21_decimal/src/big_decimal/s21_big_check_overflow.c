#include "../s21_decimal.h"

int s21_big_check_overflow(s21_big_decimal d) {
  // 0 - without overflow
  // 1 - OVERFLOW
  int overflow = 0;
  s21_big_decimal tmp_d = d;
  s21_big_decimal res_d = d;
  s21_big_decimal rem_d = {0};
  s21_big_decimal one_d = {{1, 0, 0, 0}};
  s21_big_decimal ten_d = {{10, 0, 0, 0}};

  int scale = get_big_scale(d);

  if (is_not_empty_big_decimal(res_d) == 0 && scale >= 28) {
    overflow = 2;
  }

  // round process
  // when last/10 remainder >= devider/2
  // then dividend +++
  for (int i = 0; i < scale; i++) {
    if (i == scale - 1) {
      s21_big_mod_mant(tmp_d, ten_d, &rem_d);
      s21_big_div_mant(tmp_d, ten_d, &res_d);
      if (rem_d.bits[0] >= ten_d.bits[0] >> 1) {
        tmp_d = res_d;
        s21_big_add_mant(tmp_d, one_d, &res_d);
      }
    } else {
      s21_big_div_mant(tmp_d, ten_d, &res_d);
    }

    tmp_d = res_d;
  }

  if (find_big_max_bit(res_d) > 95) {
    overflow = 1;
  }

  return overflow;
}