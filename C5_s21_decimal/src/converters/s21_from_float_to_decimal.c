#include <math.h>

#include "../s21_decimal.h"

// convert float to decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0, scale = 0, flag = 0, count = 0;
  long double tempsrc = src;
  if (fabs(src) > 0) flag = 1;
  if (src == NAN || dst == NULL || src == 1.0 / 0.0) {
    error = 1;
    if (dst != NULL) {
      clear_decimal(dst);
    }
  } else {
    clear_decimal(dst);
    int binExp = get_exp_float(src);
    if (binExp > 95 || binExp < -95) {
      error = 1;
    } else {
      while (tempsrc < 999999 && tempsrc > -999999 && scale < 28 &&
             scale > -28) {
        tempsrc *= 10;
        scale++;
      }
      // float tempf  = src;
      while (tempsrc > 10000000 || tempsrc < -10000000) {
        tempsrc /= 10;
        scale--;
        count++;
      }
      // src = src / pow(10, count);
    }
    if (scale < -28) {
      error = 1;
    } else {
      tempsrc = roundl(tempsrc);
      int temp = (int)tempsrc;
      if (temp < 0) {
        temp *= -1;
      }
      dst->bits[0] = temp;
      if (flag && scale > 0) {
        discarding_zeros(dst, &scale);
      }
      if (scale < 0) {
        negScale(dst, &scale);
      }
      set_scale(dst, scale);
      if (src < 0) {
        set_bit(dst, 127);
      }
    }
  }
  return error;
}

// converts float to decimal
// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     int error = 0, scale = 0, flag = 0, count = 0;
//     if (fabs(src) > 0) flag = 1;
//     if (src == NAN || dst == NULL || src == 1.0 / 0.0 ) {
//         error = 1;
//         if (dst != NULL) {
//             clear_decimal(dst);
//         }
//     } else {
//     clear_decimal(dst);
//         int binExp = get_exp_float(src);
//         if (binExp > 95 || binExp < -95) {
//             error = 1;
//         } else {
//             while (src < 999999 && src > -999999 && scale < 28 && scale >
//             -28) {
//                 src *= 10;
//                 scale++;

//             }
//             // float tempf  = src;
//             while (src > 10000000 || src < -10000000) {
//                 src /= 10;
//                 scale--;
//                 count++;
//             }
//             // src = src / pow(10, count);
//         }
//         if (scale < -28) {
//             error = 1;
//         } else {
//             // src = roundf(src);
//             int temp = (int)(roundf(src));
//             if (temp < 0){
//                 temp *= -1;
//             }
//             dst->bits[0] = temp;
//             if (flag && scale > 0) {
//              discarding_zeros(dst,&scale);
//             }
//                         if (scale < 0) {
//                 negScale(dst, &scale);
//             }
//             set_scale(dst, scale);
//             if (src < 0) {
//                 set_bit (dst, 127);
//             }
//         }
//     }
//     return error;
// }