#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, scale = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal tmpRes = {0};
    s21_decimal temp = {0};
    temp.bits[0] = 10;
    int sign = get_sign(value);
    scale = get_scale(value);
    for (int i = 0; i < scale; i++) {
      s21_div_mant(value, temp, &tmpRes);
      value = tmpRes;
    }
    *result = value;
    if (sign) {
      set_bit(result, 127);
    }
  }
  return error;
}
