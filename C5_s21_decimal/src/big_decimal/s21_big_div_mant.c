#include "../s21_decimal.h"

int s21_big_div_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  // 0 - без остатка
  // 1 - с остатком
  int error = 0;
  clear_big_decimal(result);
  s21_big_decimal remainder = {0};
  s21_big_decimal tmp_d = {0};
  for (int i = 191; i >= 0; i--) {
    left_big_shift_own(&remainder, 1);

    int tmp = get_big_bit(value_1, i);
    if (tmp) {  // shift dividend and add next bit to remainder
      set_big_bit(&remainder, 0);
    }

    if (s21_is_greater_big_mant(remainder, value_2) <= 1) {
      s21_big_sub_mant(remainder, value_2, &tmp_d);
      remainder = tmp_d;
      set_big_bit(result, i);
    }
  }
  // printf("Остаток от деления:    ");
  // show_bits(remainder);
  // printf("Целочисленное деление: ");
  // show_bits(*result);
  if (check_null_big_mant(remainder)) {
    error = 1;
  }
  return error;
}