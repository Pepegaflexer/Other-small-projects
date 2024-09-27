#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>

typedef enum { NORM, S21_INF, S21_N_INF, S21_NAN, DOP_CODE } value_type_t;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

enum { LOW, MID, HIGHT, SCALE };

// big_decimal
int get_big_bit(s21_big_decimal d, int i);
int set_big_bit(s21_big_decimal *d, int i);
int set_big_scale(s21_big_decimal *d, int scale);
void set_big_sign(s21_big_decimal *d);
void clear_big_sign(s21_big_decimal *d);
int clear_big_bit(s21_big_decimal *d, int i);
int copy_to_big(s21_big_decimal *dst, s21_decimal src);
int get_big_scale(s21_big_decimal d);
void show_big_bits(s21_big_decimal d);
int get_big_sign(s21_big_decimal d);
void show_big_decimal(s21_big_decimal d);
void clear_big_decimal(s21_big_decimal *d);
int find_big_max_bit(s21_big_decimal d);
int left_big_shift(s21_big_decimal d, s21_big_decimal *result, int shift);
int left_big_shift_own(s21_big_decimal *d, int shift);
void copy_big_to_big(s21_big_decimal *dst, s21_big_decimal src);
int check_null_big_mant(s21_big_decimal d);
int is_not_empty_big_decimal(s21_big_decimal d);
void s21_big_mul_mant_int(s21_big_decimal *d, int mul);
void s21_big_div_mant_int(s21_big_decimal *d, int div);
int s21_is_big_equal_zero(s21_big_decimal d);
void s21_big_round(s21_big_decimal *d, int num);

int s21_is_greater_big_mant(s21_big_decimal d1, s21_big_decimal d2);
int s21_big_mod_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_from_big_to_norm_decimal(s21_decimal *dst, s21_big_decimal src);

int big_normalize(s21_big_decimal *d1, s21_big_decimal *d2);
int s21_big_check_overflow(s21_big_decimal d);

// arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_mant(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_mant(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_mant(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_mant(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod_mant(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_big_mul_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_big_add_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_big_div_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_big_sub_mant(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

// comparision operators
int s21_is_less(s21_decimal d1, s21_decimal d2);
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_greater(s21_decimal d1, s21_decimal d2);
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_equal(s21_decimal d1, s21_decimal d2);
int s21_is_not_equal(s21_decimal d1, s21_decimal d2);
int s21_dec_comparision(s21_decimal d1, s21_decimal d2);

// converters
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// helpers
int get_bit(s21_decimal d, int i);
int set_bit(s21_decimal *d, int i);
int clear_bit(s21_decimal *d, int i);
void show_bits(s21_decimal d);
int find_max_bit(s21_decimal d);
int left_shift(s21_decimal d, s21_decimal *result, int shift);
int left_shift_own(s21_decimal *d, int shift);
int right_shift_own(s21_decimal *d, int shift);
void clear_decimal(s21_decimal *d);
int s21_is_greater_mant(s21_decimal d1, s21_decimal d2);
int bitwise_divide(s21_decimal dividend, s21_decimal divisor);
void show_decimal(s21_decimal d);
void s21_div_mant_int(s21_decimal *d, int div);
int s21_is_equal_zero(s21_decimal d);
void show_hex_decimal(s21_decimal d);
void show_bits_float(float src);
int get_exp_float(float src);
int get_mantis_float(float src);
void discarding_zeros(s21_decimal *dst, int *scale);
void negScale(s21_decimal *src, int *scale);

// for scale and sign
int get_scale(s21_decimal d);
int set_scale(s21_decimal *d, int scale);
int get_sign(s21_decimal d);
void set_sign(s21_decimal *d);

#endif  // SRC_S21_DECIMAL_H_