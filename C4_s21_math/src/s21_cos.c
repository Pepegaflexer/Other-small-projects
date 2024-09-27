#include "s21_math.h"

long double s21_cos(double x) {
  long double res = 0.0;
  if (s21_fabs(x) == S21_INF || s21_isNan(x)) {
    res = S21_NAN;
  } else {
    x = rotate_circle(x);
    if (x == S21_PI || x == S21_2PI || x == 0.0) {
      res = 1.0;
      if (x == S21_PI) {
        res = -1.0;
      }
    } else {
      res = 1.0;
      double tailor = 1.0;
      for (long double i = 1; s21_fabs(tailor) > 1e-12; i += 1) {
        tailor = ((-tailor) * x * x) / ((2.0 * i) * (2.0 * i - 1));
        res += tailor;
        if (i > 1500) {
          break;
        }
      }
    }
  }
  return res;
}
