// #include <math.h>
#include "../s21_decimal.h"

// convers decimal to int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    *dst = 0;
    s21_decimal temp = {0};
    s21_truncate(src, &temp);
    if (temp.bits[2] != 0 || temp.bits[1] != 0) {
      error = 1;
    } else {
      if ((temp.bits[0] > 2147483647 && !get_bit(temp, 127)) ||
          (temp.bits[0] > 2147483648 && get_bit(temp, 127))) {
        error = 1;
      } else {
        if (get_bit(temp, 127) > 0) {
          *dst = temp.bits[0] * -1;
        } else {
          *dst = temp.bits[0];
        }
      }
    }
  }
  return error;
}