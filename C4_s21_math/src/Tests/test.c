#include "test.h"
int run_tests(Suite *test_case) {
  int number_failed;
  SRunner *sr = srunner_create(test_case);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}

int main() {
  int number_failed = 0;
  Suite *suites_list[] = {test_abs_suite(),   test_fabs_suite(),
                          test_atan_suite(),  test_asin_suite(),
                          test_acos_suite(),  test_sin_suite(),
                          test_cos_suite(),   test_tan_suite(),
                          test_floor_suite(), test_ceil_suite(),
                          test_fmod_suite(),  test_log_suite(),
                          test_sqrt_suite(),  test_exp_suite(),
                          test_pow_suite(),   NULL};
  for (Suite **current = suites_list; *current != NULL; current++) {
    printf("_______________________________________\n");
    number_failed += run_tests(*current);
  }

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  // double test = 1.0000009999999999;
  // long double res1 = s21_atan(test);
  // long double res2 = atan(test);
  // printf("%.20Lf | %.20Lf\n", res1, res2);
  // return 0;
}
