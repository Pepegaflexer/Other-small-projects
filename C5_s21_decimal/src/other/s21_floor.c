#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_decimal edinica = {{1, 0, 0, 0}};
  s21_decimal nolik = {{0, 0, 0, 0}};
  s21_decimal desatka = {{10, 0, 0, 0}};
  s21_decimal tempd = {0};
  if (result == NULL) {
    error = 1;
  } else {
    clear_decimal(result);
    s21_truncate(value, result);
    int scale = get_scale(value);
    set_scale(&desatka, scale);
    if (s21_is_equal(*result, nolik)) {
      clear_decimal(result);
    } else if (s21_is_less(*result, nolik)) {
      if (s21_mod_mant(value, desatka, &tempd)) {
        s21_decimal temp = *result;
        s21_add_mant(temp, edinica, result);
        set_bit(result, 127);
      }
    }
  }
  return error;
}
