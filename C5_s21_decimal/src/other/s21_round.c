#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    int sign = get_sign(value);
    clear_bit(&value, 127);
    s21_decimal odin = {{1, 0, 0, 0}};
    s21_decimal five = {{5, 0, 0, 0}};
    set_scale(&five, 1);
    s21_decimal remainder = {{0, 0, 0, 0}};
    s21_truncate(value, &remainder);
    s21_sub(value, remainder, &remainder);  // берем остаток
    s21_truncate(value, &value);
    if (s21_is_greater_or_equal(remainder, five)) {
      error = s21_add(value, odin, result);  // +1
    } else {
      *result = value;
    }
    if (sign) {
      set_sign(result);  // если отрицательное, возвращаем знак
    }
  }
  return error;
}
