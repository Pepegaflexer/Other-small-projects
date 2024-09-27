#include "s21_math.h"
#define S21_PI_12 (S21_PI / 12.0)
#define S21_PI_6 (S21_PI / 6.0)
#define S21_PI_2 (S21_PI / 2.0)
#define S21_SQRT_3 1.73205080756887729

long double s21_atan(double x) {
  long double res = 0.0;
  if (s21_fabs(x) == 1.) {
    res = S21_PI / 4.;
    if (x < 0.) {
      res = -res;
    }
  } else if (s21_fabs(x) == S21_INF) {
    res = S21_PI / 2;
    if (x == -S21_INF) {
      res = -res;
    }
  } else {
    int over_one = 0, neg = 0, size = 0;
    long double x2 = 0.0;
    if (x < 0.0) {
      x = -x;
      neg = 1;
    }
    if (x > s21_pow(10, 7)) {
      x = s21_pow(10, 7);
    }
    if (x > 1.0) {
      x = 1.0 / x;
      over_one = 1;
    }
    /* сужение области определения */
    while (x > S21_PI_12) {
      size++;
      res = 1.0 / (x + S21_SQRT_3);
      x = ((x * S21_SQRT_3) - 1) * res;
    }
    x2 = x * x;
    /* форрмула для аппроксимации (ист. VS FORTRAN
  Application Programming: Library Reference) */
    res = (0.60310579 - 0.05160454 * x2 + 0.55913709 / (x2 + 1.4087812)) * x;
    /* возврат области определения */
    while (size > 0) {
      res += S21_PI_6;
      size--;
    }
    if (over_one == 1) {
      res = S21_PI_2 - res;
    }
    if (neg == 1) {
      res = -res;
    }
  }
  return res;
}
