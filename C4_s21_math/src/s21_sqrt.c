#include "s21_math.h"

long double s21_sqrt(double x) {
  long double left = 0;
  long double right = s21_maxvalue(x);
  long double mid = 0;
  mid = (left + right) / 2;

  while ((mid - left) > S21_EPS) {
    if ((mid * mid) > x) {
      right = mid;
    } else {
      left = mid;
    }
    mid = (left + right) / 2;
  }
  if (x < 0) {
    mid = S21_NAN;
  } else if (x == S21_INF || s21_isNan(x)) {
    mid = x;
  }
  return mid;
}

double s21_maxvalue(double x) {
  double result = 1;
  if (x > 1) {
    result = x;
  }
  return result;
}
