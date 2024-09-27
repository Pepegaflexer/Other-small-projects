#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_math.h"

#define EPS_FOR_TEST 1e-6

Suite *test_abs_suite(void);
Suite *test_fabs_suite(void);
Suite *test_atan_suite(void);
Suite *test_asin_suite(void);
Suite *test_acos_suite(void);
Suite *test_sin_suite(void);
Suite *test_cos_suite(void);
Suite *test_tan_suite(void);
Suite *test_floor_suite(void);
Suite *test_ceil_suite(void);
Suite *test_fmod_suite(void);
Suite *test_log_suite(void);
Suite *test_sqrt_suite(void);
Suite *test_exp_suite(void);
Suite *test_pow_suite(void);

#endif  //  SRC_TESTS_TEST_H_
