#include "s21_math.h"

long double s21_ceil(double x) {
  long double res = (long long)(x);
  if (s21_fabs(x) == S21_INF || s21_isNan(x)) {
    res = x;
  } else if (x > 0.0 && res != x) {
    res += 1;
  }
  return res;
}
