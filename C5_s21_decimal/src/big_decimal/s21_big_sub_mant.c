#include "../s21_decimal.h"

// if value_1 < value_2, then sign in result will be minus
int s21_big_sub_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int error = DOP_CODE;
  int greater = s21_is_greater_big_mant(value_1, value_2);
  clear_big_decimal(result);

  s21_big_decimal bigger_d = {0};
  s21_big_decimal smaller_d = {0};

  s21_big_decimal one_d = {{1, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal tmp_d = {0};
  if (greater == 1) {
    smaller_d.bits[0] = ~value_2.bits[0];
    smaller_d.bits[1] = ~value_2.bits[1];
    smaller_d.bits[2] = ~value_2.bits[2];
    smaller_d.bits[3] = ~value_2.bits[3];
    smaller_d.bits[4] = ~value_2.bits[4];
    smaller_d.bits[5] = ~value_2.bits[5];
    bigger_d = value_1;
  } else {
    smaller_d.bits[0] = ~value_1.bits[0];
    smaller_d.bits[1] = ~value_1.bits[1];
    smaller_d.bits[2] = ~value_1.bits[2];
    smaller_d.bits[3] = ~value_1.bits[3];
    smaller_d.bits[4] = ~value_1.bits[4];
    smaller_d.bits[5] = ~value_1.bits[5];
    bigger_d = value_2;
  }
  s21_big_add_mant(smaller_d, one_d, &tmp_d);
  s21_big_add_mant(bigger_d, tmp_d, result);
  if (greater == 2) {
    set_big_sign(result);
  }
  return error;
}