#include "../s21_decimal.h"

// comparision two decimals, 0 - is equal, 1 - first is greater, 2 - second is
// greater
int s21_dec_comparision(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  int sign_d1 = get_sign(d1);
  int sign_d2 = get_sign(d2);
  int zero = s21_is_equal_zero(d1) && s21_is_equal_zero(d2);

  s21_big_decimal tmp_d1 = {0};
  s21_big_decimal tmp_d2 = {0};
  copy_to_big(&tmp_d1, d1);
  copy_to_big(&tmp_d2, d2);
  big_normalize(&tmp_d1, &tmp_d2);
  int greater = s21_is_greater_big_mant(tmp_d1, tmp_d2);

  if (zero) {
    result = 0;
  } else if (!sign_d1 && sign_d2) {
    result = 1;
  } else if (sign_d1 && !sign_d2) {
    result = 2;
  } else if (!sign_d1 && !sign_d2) {  // both are positive
    result = greater;
  } else if (sign_d1 && sign_d2) {  // both are negative
    if (greater == 2) {
      result = 1;
    } else if (greater == 1) {
      result = 2;
    }
  }
  return result;
}

// comparision of mantissas, 0 - is equal, 1 - first is greater, 2 - second is
// greater
int s21_is_greater_mant(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  for (int i = 2; i >= 0 && !result; i--) {
    if (d1.bits[i] > d2.bits[i]) {
      result = 1;
    } else if (d1.bits[i] < d2.bits[i]) {
      result = 2;
    }
  }
  return result;
}
