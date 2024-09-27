#include <math.h>

#include "../s21_decimal.h"

// converts int to decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    clear_decimal(dst);
    if (src < 0) {
      set_bit(dst, 127);
      src *= -1;
    }
    dst->bits[0] = src;
  }
  return error;
}