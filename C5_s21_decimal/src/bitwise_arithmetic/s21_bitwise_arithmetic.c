#include "../s21_decimal.h"

int s21_add_mant(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  clear_decimal(result);
  int error = 0;
  int tmp = 0;
  int left_bit = 0;
  int right_bit = 0;
  for (int i = 0; i <= 95; i++) {
    left_bit = get_bit(value_1, i);
    right_bit = get_bit(value_2, i);

    if (left_bit & right_bit) {
      if (tmp) {
        set_bit(result, i);
      }
      tmp = 1;
    } else if (left_bit ^ right_bit) {
      if (!tmp) {
        set_bit(result, i);
      }
    } else if (!(left_bit | right_bit)) {
      if (tmp) {
        set_bit(result, i);
        tmp = 0;
      }
    }
  }
  if (tmp) {
    error = S21_INF;
  }
  return error;
}

// subtraction from greater than less without sign processing
int s21_sub_mant(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = DOP_CODE;
  clear_decimal(result);
  s21_decimal temp = value_2;
  s21_decimal temp1 = {0};
  s21_decimal temp2 = {0};
  temp1.bits[0] = 1;
  temp.bits[0] = ~value_2.bits[0];
  temp.bits[1] = ~value_2.bits[1];
  temp.bits[2] = ~value_2.bits[2];
  s21_add_mant(temp, temp1, &temp2);
  s21_add_mant(value_1, temp2, result);
  return error;
}

int s21_mul_mant(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  clear_decimal(result);
  int error = 0;
  int max_bit = find_max_bit(value_1);
  s21_decimal tmp_d = {0};
  for (int i = 0; i <= max_bit; i++) {
    if (get_bit(value_1, i)) {
      left_shift(value_2, &tmp_d, i);
      s21_add_mant(*result, tmp_d, result);
    }
  }
  return error;
}

int s21_div_mant(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  clear_decimal(result);
  int error = 0;
  s21_decimal remainder = {0};
  s21_decimal tmp_d = {0};
  for (int i = 95; i >= 0; i--) {
    left_shift_own(&remainder, 1);

    int tmp = get_bit(value_1, i);
    if (tmp) {  // shift dividend and add next bit to remainder
      set_bit(&remainder, 0);
    }

    if (s21_is_greater_mant(remainder, value_2) <= 1) {
      s21_sub_mant(remainder, value_2, &tmp_d);
      remainder = tmp_d;
      set_bit(result, i);
    }
  }
  return error;
}

int s21_mod_mant(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  // 0 - без остатка
  // 1 - с остатком
  int error = 0;
  clear_decimal(result);
  s21_decimal remainder = {0};
  s21_decimal tmp_d = {0};
  for (int i = 95; i >= 0; i--) {
    left_shift_own(&remainder, 1);

    int tmp = get_bit(value_1, i);
    if (tmp) {  // shift dividend and add next bit to remainder
      set_bit(&remainder, 0);
    }

    if (s21_is_greater_mant(remainder, value_2) <= 1) {
      s21_sub_mant(remainder, value_2, &tmp_d);
      remainder = tmp_d;
      set_bit(result, i);
    }
  }
  *result = remainder;
  if (!s21_is_equal_zero(remainder)) {
    error = 1;
  }
  return error;
}
