#include "s21_math.h"

long double s21_exp(double x) {
  long double res = 1;
  long double shag = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  for (long double i = 1; s21_fabs(shag) > 1e-13; i++) {
    shag *= x / i;
    res += shag;
    if (s21_fabs(res) > S21_DBL_MAX) {
      res = S21_INF;
      break;
    }
    if (i > 1500) {
      break;
    }
  }
  if (flag == 1) {
    if (res > S21_DBL_MAX) {
      res = 0;
    } else {
      res = 1 / res;
    }
  }
  return res;
}
