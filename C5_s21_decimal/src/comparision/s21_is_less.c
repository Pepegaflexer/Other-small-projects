#include "../s21_decimal.h"

// is first is less then second? 0 - FALSE, 1 - TRUE
int s21_is_less(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  if (s21_dec_comparision(d1, d2) == 2) {
    result = 1;
  }
  return result;
}
