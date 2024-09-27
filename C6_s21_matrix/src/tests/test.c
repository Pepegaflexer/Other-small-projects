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
  Suite *suites_list[] = {test_create_suite(),
                          test_eq_suite(),
                          test_sum_suite(),
                          test_sub_suite(),
                          test_mul_num_suite(),
                          test_mul_mat_suite(),
                          test_trans_suite(),
                          test_det_suite(),
                          test_compl_suite(),
                          test_inv_suite(),
                          NULL};
  for (Suite **current = suites_list; *current != NULL; current++) {
    printf("_______________________________________\n");
    number_failed += run_tests(*current);
  }

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
