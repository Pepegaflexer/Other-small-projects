#include "s21_math.h"

long double s21_acos(double x) {
  long double res = S21_PI / 2;
  if (x >= 0. && x < 1.) {
    if (x != 0.) {
      res = s21_atan(s21_sqrt(1 - x * x) / x);
    }
  } else if (x > -1. && x < 0.) {
    res = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (s21_fabs(x) == 1.) {
    res = 0.;
    if (x < 0) {
      res = S21_PI;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}
