#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

Suite *test_create_suite(void);
Suite *test_eq_suite(void);
Suite *test_sum_suite(void);
Suite *test_sub_suite(void);
Suite *test_mul_num_suite(void);
Suite *test_mul_mat_suite(void);
Suite *test_trans_suite(void);
Suite *test_det_suite(void);
Suite *test_compl_suite(void);
Suite *test_inv_suite(void);

#endif  //  SRC_TESTS_TEST_H_
