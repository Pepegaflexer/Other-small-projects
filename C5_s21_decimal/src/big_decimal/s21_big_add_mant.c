#include "../s21_decimal.h"

int s21_big_add_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  clear_big_decimal(result);
  int error = 0;
  int tmp = 0;
  int left_bit = 0;
  int right_bit = 0;
  for (int i = 0; i <= 191; i++) {  // ????
    left_bit = get_big_bit(value_1, i);
    right_bit = get_big_bit(value_2, i);

    if (left_bit & right_bit) {
      if (tmp) {
        set_big_bit(result, i);
      }
      tmp = 1;
    } else if (left_bit ^ right_bit) {
      if (!tmp) {
        set_big_bit(result, i);
      }
    } else if (!(left_bit | right_bit)) {
      if (tmp) {
        set_big_bit(result, i);
        tmp = 0;
      }
    }
  }
  if (tmp) {
    // clear_decimal(result);
    error = S21_INF;
  }
  // необходимо проверить на переполнение
  // если tmp == 1, result очистить и поместить тип INF
  // вернуть код ошибки

  return error;
}