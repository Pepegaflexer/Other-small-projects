#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    *result = value;
    if (get_sign(value)) {
      clear_bit(result, 127);
    } else {
      set_bit(result, 127);
    }
  }
  return error;
}
