#include "s21_math.h"

long double s21_sin(double x) {
  long double res = 0.0;
  if (s21_fabs(x) == S21_INF || s21_isNan(x)) {
    res = S21_NAN;
  } else {
    x = rotate_circle(x);
    if (x == 0.0 || x == 3 * S21_PI / 2 || x == S21_PI / 2) {
      if (x == S21_PI / 2) {
        res = 1.0;
      } else if (x == 3 * S21_PI / 2) {
        res = -1.0;
      }
    } else {
      res = x;
      double tailor = x;
      for (long double i = 1; s21_fabs(tailor) > S21_EPS; i += 1) {
        tailor = ((-tailor) * x * x) / ((2.0 * i + 1) * 2.0 * i);
        res += tailor;
        if (i > 1500) {
          break;
        }
      }
    }
  }
  return res;
}

double rotate_circle(double x) {
  while (s21_fabs(x) > S21_2PI) {
    if (x > S21_2PI) {
      x -= S21_2PI;
    } else {
      x += S21_2PI;
    }
  }
  return x;
}
