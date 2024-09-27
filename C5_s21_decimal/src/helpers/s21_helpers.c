#include "../s21_decimal.h"

int get_bit(s21_decimal d, int i) {
  int res = 0;
  int mask = 1 << i % 32;
  if (d.bits[i / 32] & mask) res = 1;
  return res;
}

int set_bit(s21_decimal *d, int i) {
  int mask = 1 << i % 32;
  d->bits[i / 32] |= mask;
  return 0;
}

int clear_bit(s21_decimal *d, int i) {
  int mask = ~(1 << i % 32);
  d->bits[i / 32] &= mask;
  return 0;
}

int find_max_bit(s21_decimal d) {
  int res = 0;
  for (int i = 95; i >= 0 && !res; i--) {
    if (get_bit(d, i)) {
      res = i;
    }
  }
  return res;
}

int left_shift(s21_decimal d, s21_decimal *result, int shift) {
  clear_decimal(result);
  int error = 0;
  int tmp = 0;
  int max_bit = find_max_bit(d);
  if ((max_bit + shift) <= 95 && shift >= 0) {
    for (int k = max_bit; k >= 0; k--) {
      tmp = get_bit(d, k);
      if (tmp) {
        set_bit(result, k + shift);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int left_shift_own(s21_decimal *d, int shift) {
  int error = 0;
  int tmp = 0;
  int max_bit = find_max_bit(*d);
  if ((max_bit + shift) <= 95 && shift >= 0) {
    for (int k = max_bit; k >= 0; k--) {
      tmp = get_bit(*d, k);
      if (tmp) {
        set_bit(d, k + shift);
        clear_bit(d, k);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

void clear_decimal(s21_decimal *d) {
  d->bits[0] = 0;
  d->bits[1] = 0;
  d->bits[2] = 0;
  d->bits[3] = 0;
}

int get_scale(s21_decimal d) {
  s21_decimal tmp_d = d;
  clear_bit(&tmp_d, 127);
  int scale = tmp_d.bits[3] >> 16;
  return scale;
}

int set_scale(s21_decimal *d, int scale) {
  int error = 0;
  int sign = get_sign(*d);
  d->bits[3] = scale << 16;
  if (sign) {
    set_bit(d, 127);
  }
  return error;
}

int get_sign(s21_decimal d) {
  // 0 - +positive
  // 1 - -negative
  int res = get_bit(d, 127);
  return res;
}

void set_sign(s21_decimal *d) { set_bit(d, 127); }

// s21_decimal == 0? 0 - FALSE, 1 - TRUE
int s21_is_equal_zero(s21_decimal d) {
  // 0 - FALSE
  // 1 - TRUE
  int res = 0;
  if (d.bits[2] == 0) {
    if (d.bits[1] == 0) {
      if (d.bits[0] == 0) {
        res = 1;
      }
    }
  }
  return res;
}

// returns the final value of the float exponent
int get_exp_float(float src) {
  int floatexp = 0;
  unsigned int fbits = *((unsigned int *)&src);
  fbits &= ~(1 << 31);
  floatexp = (fbits >> 23) - 127;
  return floatexp;
}

// discarding zeros
void discarding_zeros(s21_decimal *dst, int *scale) {
  if (dst->bits[0] != 0) {
    while (dst->bits[0] % 10 == 0) {
      dst->bits[0] /= 10;
      *scale = *scale - 1;
    }
  }
}

void negScale(s21_decimal *src, int *scale) {
  s21_decimal temp1 = {0}, temp2 = *src;
  temp1.bits[0] = 10;
  while (*scale < 0) {
    s21_mul_mant(temp2, temp1, src);
    *scale += 1;
    temp2 = *src;
  }
}
