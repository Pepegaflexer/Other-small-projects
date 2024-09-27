#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *test_add_suite(void);
Suite *test_sub_suite(void);
Suite *test_div_suite(void);
Suite *test_mul_suite(void);
Suite *test_mod_suite(void);
Suite *test_comp_suite(void);
Suite *test_from_float_to_decimal(void);
Suite *test_from_int_to_decimal(void);
Suite *test_from_decimal_to_int(void);
Suite *test_from_decimal_to_float(void);
Suite *test_floor_suite(void);
Suite *test_negate_suite(void);
Suite *test_round_suite(void);
Suite *test_truncate_suite(void);

#endif  //  SRC_TESTS_TEST_H_
