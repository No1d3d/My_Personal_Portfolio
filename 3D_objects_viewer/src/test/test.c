#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../C_Backend/3dviewer.h"

START_TEST(test_1) {
  // char str[] = "./C_Backend/test.c";
  char str[] = "./obj/cube.obj";
  object_s qwe = {0};
  parser(str, &qwe);
  ck_assert_int_eq(qwe.facets_count, 30);
  ck_assert_int_eq(qwe.vertex_count, 8);
  ck_assert_double_eq(qwe.vertex_array[0], 0);
  ck_assert_double_eq(qwe.facets_array[0], 0);
  delta delta = {0};
  normalizationFunction(&qwe);
  rotationFunction(&qwe, 0, XAxis);
  rotationFunction(&qwe, 0, YAxis);
  rotationFunction(&qwe, 0, ZAxis);
  shiftFunction(&qwe, delta, XAxis);
  shiftFunction(&qwe, delta, YAxis);
  shiftFunction(&qwe, delta, ZAxis);
  scaleFunction(&qwe, 1);
  free(qwe.facets_array);
  free(qwe.vertex_array);
}
END_TEST

Suite *tests() {
  Suite *s = suite_create("TEST");
  TCase *tc = tcase_create("all test");
  tcase_add_test(tc, test_1);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int nf = 0;
  Suite *suite = tests();
  SRunner *test_1 = srunner_create(suite);
  srunner_set_fork_status(test_1, CK_NOFORK);
  srunner_run_all(test_1, CK_NORMAL);
  nf += srunner_ntests_failed(test_1);
  srunner_free(test_1);
  return nf == 0 ? 0 : 1;
}
