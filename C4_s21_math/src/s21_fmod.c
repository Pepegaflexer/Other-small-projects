#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = 0.0;
  if (s21_fabs(x) == S21_INF || s21_isNan(x) || y == 0.0) {
    res = S21_NAN;
  } else if (s21_fabs(x) <= s21_fabs(y)) {
    res = x;
    if (x == y) {
      res = 0;
    }
  } else {
    long long count = x / y;
    res = x - count * y;
  }
  return res;
}
