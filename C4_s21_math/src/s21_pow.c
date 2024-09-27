#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double res = 0;
  if (s21_isNan(base) || s21_isNan(exp)) {
    res = S21_NAN;
  } else if (s21_fabs(exp) == S21_INF && base != 0) {
    res = 1.0;
    if (s21_fabs(base) != 1) {
      if (exp > 0) {
        res = S21_INF;
      } else {
        res = 0.0;
      }
    }
  } else if (exp == 0 || base == 0) {
    if (exp == 0) {
      res = 1;
    } else {
      res = 0;
    }
  } else if (base < 0 && (exp - (long)exp) != 0.0) {
    res = S21_NAN;
  } else {
    if (exp == (long)exp && exp < 10000 && exp > 0) {
      res = whole_exp_pow(base, (long)exp);
    } else {
      res = s21_exp(exp * s21_log(s21_fabs(base)));
      if (base < 0 && s21_fmod(exp, 2.0) != 0.0) {
        res *= -1;
      }
    }
  }
  return res;
}

long double whole_exp_pow(double base, long exp) {
  long double res = 1;
  for (int i = 0; i < exp; i++) {
    res *= base;
  }
  return res;
}