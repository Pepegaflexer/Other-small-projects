#include "s21_math.h"

long double s21_log(double x) {
  long double res = 0.0;
  if (x < 0.0 || s21_isNan(x)) {
    res = S21_NAN;
  } else if (s21_fabs(x) == S21_INF || x == 0.0) {
    res = S21_INF;
    if (x == 0.0) {
      res = -S21_INF;
    }
  } else if (x == 1.0) {
    res = 0.0;
  } else {
    long double count = 0.0;
    while (x >= S21_EXP) {
      x /= S21_EXP;
      count++;
    }
    long double increment = 1.0;
    for (long double i = 0; s21_fabs(increment) > 1e-11; i++) {
      increment = 2 * (x - s21_exp(res)) / (x + s21_exp(res));
      res += increment;
      if (i > 1500) {
        break;
      }
    }
    res += count;
  }
  return res;
}
