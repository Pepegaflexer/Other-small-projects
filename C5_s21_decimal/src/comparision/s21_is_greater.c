#include "../s21_decimal.h"

// is first is greater then second? 0 - FALSE, 1 - TRUE
int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  if (s21_dec_comparision(d1, d2) == 1) {
    result = 1;
  }
  return result;
}