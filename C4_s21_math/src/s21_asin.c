#include "s21_math.h"

long double s21_asin(double x) {
  long double res = 0.0;
  if (s21_fabs(x) < 1.) {
    if (x != 0.) {
      res = s21_atan(x / s21_sqrt(1 - x * x));
    }
  } else if (s21_fabs(x) == 1.) {
    res = S21_PI / 2;
    if (x < 0) {
      res = -res;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}
