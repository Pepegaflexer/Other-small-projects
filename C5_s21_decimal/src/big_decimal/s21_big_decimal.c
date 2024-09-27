#include "../s21_decimal.h"

int set_big_bit(s21_big_decimal *d, int i) {
  int error = 0, mask = 0;
  if (i > 223) {
    error = 1;
  } else {
    mask = 1 << i % 32;
    d->bits[i / 32] |= mask;
  }
  return error;
}

int clear_big_bit(s21_big_decimal *d, int i) {
  int mask = ~(1 << i % 32);
  d->bits[i / 32] &= mask;
  return 0;
}

int copy_to_big(s21_big_decimal *dst, s21_decimal src) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[6] = src.bits[3];
  return 0;
}

int get_big_bit(s21_big_decimal d, int i) {
  int res = 0;
  int mask = 1 << i % 32;
  if (d.bits[i / 32] & mask) res = 1;
  return res;
}

int get_big_scale(s21_big_decimal d) {
  int mask = 0xff << 16;
  int scale = d.bits[6] & mask;
  scale >>= 16;
  return scale;
}

int get_big_sign(s21_big_decimal d) {
  // 0 - +positive
  // 1 - -negative
  int res = get_big_bit(d, 223);
  return res;
}

void clear_big_decimal(s21_big_decimal *d) {
  d->bits[0] = 0;
  d->bits[1] = 0;
  d->bits[2] = 0;
  d->bits[3] = 0;
  d->bits[4] = 0;
  d->bits[5] = 0;
  d->bits[6] = 0;
}

int find_big_max_bit(s21_big_decimal d) {
  int res = -1;  // ????
  for (int i = 191; i >= 0 && res < 0; i--) {
    if (get_big_bit(d, i)) {
      res = i;
    }
  }
  return res;
}

int left_big_shift(s21_big_decimal d, s21_big_decimal *result, int shift) {
  clear_big_decimal(result);
  int error = 0;
  int tmp = 0;
  int max_bit = find_big_max_bit(d);
  if ((max_bit + shift) <= 191 && shift >= 0) {
    for (int k = max_bit; k >= 0; k--) {
      tmp = get_big_bit(d, k);
      if (tmp) {
        set_big_bit(result, k + shift);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int left_big_shift_own(s21_big_decimal *d, int shift) {
  int error = 0;
  int tmp = 0;
  int max_bit = find_big_max_bit(*d);
  if ((max_bit + shift) <= 191 && shift >= 0) {
    for (int k = max_bit; k >= 0; k--) {
      tmp = get_big_bit(*d, k);
      if (tmp) {
        set_big_bit(d, k + shift);
        clear_big_bit(d, k);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

// comparision of mantissas, 0 - is equal, 1 - first is greater, 2 - second is
// greater
int s21_is_greater_big_mant(s21_big_decimal d1, s21_big_decimal d2) {
  int result = 0;
  for (int i = 5; i >= 0 && !result; i--) {
    if (d1.bits[i] > d2.bits[i]) {
      result = 1;
    } else if (d1.bits[i] < d2.bits[i]) {
      result = 2;
    }
  }
  return result;
}

int set_big_scale(s21_big_decimal *d, int scale) {
  int error = 0;
  int sign = get_big_bit(*d, 223);
  d->bits[6] = scale << 16;
  if (sign) {
    set_big_bit(d, 223);
  }
  return error;
}

void set_big_sign(s21_big_decimal *d) { set_big_bit(d, 223); }

int check_null_big_mant(s21_big_decimal d) {
  // 0 - все нули
  // 1 - есть значение
  int result = 0;
  for (int i = 5; i >= 0; i--) {
    if (d.bits[i]) {
      result = 1;
    }
  }
  return result;
}

// 0 - FALSE (is empty), 1 - TRUE (is not empty)
int is_not_empty_big_decimal(s21_big_decimal d) {
  int result = 0;
  for (int i = 5; i >= 0 && !result; i--) {
    if (d.bits[i] != 0) {
      result = 1;
    }
  }
  return result;
}

// big_decimal x int
void s21_big_mul_mant_int(s21_big_decimal *d, int mul) {
  s21_big_decimal mul_d = {{0}};
  s21_big_decimal tmp_d = *d;
  mul_d.bits[0] = mul;
  s21_big_mul_mant(tmp_d, mul_d, d);
}

// big_decimal / int
void s21_big_div_mant_int(s21_big_decimal *d, int div) {
  s21_big_decimal div_d = {{0}};
  s21_big_decimal tmp_d = *d;
  div_d.bits[0] = div;
  s21_big_div_mant(tmp_d, div_d, d);
}

// s21_decimal == 0? 0 - FALSE, 1 - TRUE
int s21_is_big_equal_zero(s21_big_decimal d) {
  // 0 - FALSE
  // 1 - TRUE
  int res = 1;
  for (int i = 0; i < 5 && res; i++) {
    if (d.bits[i] != 0) {
      res = 0;
    }
  }
  return res;
}

void s21_big_round(s21_big_decimal *d, int num) {
  s21_big_decimal src_d = *d;
  s21_big_decimal tmp_d = *d;
  s21_big_decimal res_d = *d;
  s21_big_decimal rem_d = {0};
  s21_big_decimal one_d = {{1, 0, 0, 0}};
  s21_big_decimal ten_d = {{10, 0, 0, 0}};
  while (num > 0) {
    s21_big_div_mant(src_d, ten_d, &res_d);
    s21_big_mod_mant(src_d, ten_d, &rem_d);
    src_d = res_d;
    num--;
  }
  if (rem_d.bits[0] > ten_d.bits[0] >> 1) {
    tmp_d = res_d;
    s21_big_add_mant(tmp_d, one_d, &res_d);
  } else if (rem_d.bits[0] == ten_d.bits[0] >> 1) {
    if (get_big_bit(res_d, 0) == 1) {
      tmp_d = res_d;
      s21_big_add_mant(tmp_d, one_d, &res_d);
    }
  }
  *d = res_d;
}