#include "../s21_decimal.h"

void show_bits(s21_decimal d) {
  for (int i = 95; i >= 0; i--) {
    int mask = 1 << i % 32;
    if (d.bits[i / 32] & mask) {
      printf("1");
    } else {
      printf("0");
    }
    if (!(i % 8) && i) {
      if (!(i % 32)) {
        printf(" ");
      }
    }
  }
  printf("\n");
}

int right_shift_own(s21_decimal *d, int shift) {
  int error = 0;
  int tmp = 0;
  int max_bit = find_max_bit(*d);
  for (int i = 0; i < shift; i++) {
    for (int k = 1; k <= max_bit; k++) {
      tmp = get_bit(*d, k);
      if (tmp) {
        set_bit(d, k - 1);
        clear_bit(d, k);
      } else {
        clear_bit(d, k - 1);
      }
    }
  }
  return error;
}

void show_decimal(s21_decimal d) {
  printf("Mant: ");
  show_bits(d);
  printf("Scale: %d\n", get_scale(d));
  printf("Sign: %d\n", get_sign(d));
}

void show_hex_decimal(s21_decimal d) {
  printf("HEX_Mant:\n");
  printf("bits[3]  bits[2]  bits[1]  bits[0]\n");
  printf("%.8X %.8X %.8X %.8X\n", d.bits[3], d.bits[2], d.bits[1], d.bits[0]);
  printf("Scale: %d\n", get_scale(d));
  printf("Sign: %d\n", get_sign(d));
}

// decimal / int
void s21_div_mant_int(s21_decimal *d, int div) {
  s21_decimal div_d = {{0}};
  s21_decimal tmp_d = *d;
  div_d.bits[0] = div;
  s21_div_mant(tmp_d, div_d, d);
}

// show all float bits
void show_bits_float(float src) {
  unsigned int fbits = *((unsigned int *)&src);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    printf("%d", !!(fbits & mask));
  }
  printf("\n");
}

// returns the mantissa of the float
int get_mantis_float(float src) {
  unsigned int floatmantis = 0;
  unsigned int fbits = *((unsigned int *)&src);
  for (int i = 2; i >= 0; i--) {
    floatmantis += fbits & (1 << i);
  }
  return floatmantis;
}

void clear_big_sign(s21_big_decimal *d) { clear_big_bit(d, 223); }

void copy_big_to_big(s21_big_decimal *dst, s21_big_decimal src) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[3];
  dst->bits[4] = src.bits[4];
  dst->bits[5] = src.bits[5];
  dst->bits[6] = src.bits[6];
}

void show_big_decimal(s21_big_decimal d) {
  printf("Mant:");
  show_big_bits(d);
  printf("Scale: %d\n", get_big_scale(d));
  printf("Sign: %d\n", get_big_sign(d));
}

void show_big_bits(s21_big_decimal d) {
  for (int i = 191; i >= 0; i--) {
    int mask = 1 << i % 32;
    if (i == 191) printf("\n5-4-3: ");
    if (i == 95) printf("\n2-1-0: ");
    if (d.bits[i / 32] & mask) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}