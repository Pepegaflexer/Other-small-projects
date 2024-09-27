#include <math.h>

#include "../s21_decimal.h"

// convert decimal to float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  long double temp = 0.0;
  if (dst == NULL) {
    error = 1;
  } else {
    *dst = 0.0;
    int scale = get_scale(src);
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        temp += pow(2, i);
      }
    }
    for (int i = 0; i < scale; i++) {
      temp /= 10;
    }
    if (get_sign(src)) {
      temp *= -1;
    }
    *dst = temp;
  }
  return error;
}