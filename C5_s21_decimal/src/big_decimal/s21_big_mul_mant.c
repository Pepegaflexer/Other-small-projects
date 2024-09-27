#include "../s21_decimal.h"

int s21_big_mul_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  clear_big_decimal(result);
  int error = 0;
  int max_bit = find_big_max_bit(value_1);
  // printf("MAXBIT %d\n", max_bit);
  s21_big_decimal tmp_d = {0};
  for (int i = 0; i <= max_bit; i++) {
    if (get_big_bit(value_1, i)) {
      left_big_shift(value_2, &tmp_d, i);
      s21_big_add_mant(*result, tmp_d, result);
    }
  }
  return error;
  // необходимо проверить на переполнение
}