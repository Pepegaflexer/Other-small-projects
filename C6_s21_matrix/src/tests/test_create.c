#include "test.h"

START_TEST(test1_create) {
  matrix_t a;
  int code = s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 2);
  ck_assert_int_eq(a.rows, 2);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test2_create) {
  matrix_t a;
  int code = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 3);
  ck_assert_int_eq(a.rows, 3);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test3_create) {
  matrix_t a;
  int code = s21_create_matrix(4, 4, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 4);
  ck_assert_int_eq(a.rows, 4);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test4_create) {
  matrix_t a;
  int code = s21_create_matrix(5, 5, &a);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(a.columns, 5);
  ck_assert_int_eq(a.rows, 5);
  ck_assert_ptr_nonnull(a.matrix);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test5_create) {
  matrix_t a;
  int code = s21_create_matrix(0, 0, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test6_create) {
  matrix_t a;
  int code = s21_create_matrix(-3, 3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test7_create) {
  matrix_t a;
  int code = s21_create_matrix(3, -3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test8_create) {
  matrix_t a;
  int code = s21_create_matrix(-3, -3, &a);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test9_create) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
}
END_TEST

Suite *test_create_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_CREATE_MATRIX=-\033[0m.");
  /* Core test case */
  tc = tcase_create("add_tc");

  tcase_add_test(tc, test1_create);
  tcase_add_test(tc, test2_create);
  tcase_add_test(tc, test3_create);
  tcase_add_test(tc, test4_create);
  tcase_add_test(tc, test5_create);
  tcase_add_test(tc, test6_create);
  tcase_add_test(tc, test7_create);
  tcase_add_test(tc, test8_create);
  tcase_add_test(tc, test9_create);

  suite_add_tcase(s, tc);

  return s;
}
