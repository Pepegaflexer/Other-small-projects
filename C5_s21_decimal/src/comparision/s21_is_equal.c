#include "../s21_decimal.h"

// is first and second are equal? 0 - FALSE, 1 - TRUE
int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  if (s21_dec_comparision(d1, d2) == 0) {
    result = 1;
  }
  return result;
}