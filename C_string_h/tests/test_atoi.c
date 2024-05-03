#include "../tests_includes/s21_tests.h"

START_TEST(atoi_test1) {
  char src[] = "  +123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test2) {
  char src[] = "  -123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test3) {
  char src[] = "0";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test4) {
  char src[] = "   -0";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test5) {
  char src[] = "+0  ";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test6) {
  char src[] = "5999999999";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test7) {
  char src[] = "-5999999999";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(atoi_test8) {
  char src[] = "9999999999";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

Suite *suite_atoi(void) {
  Suite *s = suite_create("suite_atoi");
  TCase *tc = tcase_create("atoi_tc");

  tcase_add_test(tc, atoi_test1);
  tcase_add_test(tc, atoi_test2);
  tcase_add_test(tc, atoi_test3);
  tcase_add_test(tc, atoi_test4);
  tcase_add_test(tc, atoi_test5);
  tcase_add_test(tc, atoi_test6);
  tcase_add_test(tc, atoi_test7);
  tcase_add_test(tc, atoi_test8);

  suite_add_tcase(s, tc);
  return s;
}
