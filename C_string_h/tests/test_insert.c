#include "../tests_includes/s21_tests.h"

START_TEST(insert_test1) {
  char str[] = "Shlepa";
  char src[] = "I love my . He is very kind!";
  s21_size_t index = 10;
  char expected[] = "I love my Shlepa. He is very kind!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test2) {
  char str[] = "Hello, ";
  char src[] = "Aboba!";
  s21_size_t index = 0;
  char expected[] = "Hello, Aboba!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test3) {
  char str[] = "";
  char src[] = "";
  s21_size_t index = 100;
  char *expected = "";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test4) {
  char *src = NULL;
  char *str = NULL;
  s21_size_t index = 100;
  char *expected = NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test5) {
  char str[] = "Monkey";
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space Monkey ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_str_null) {
  char *str = NULL;
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space  ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert_1) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

// START_TEST(test_insert_2) {
//   char s1[30] = "";
//   char s3[] = "";
//   char *s4 = S21_NULL;
//   s21_size_t num = 7;
//   char *s2 = s21_insert(s1, s3, num);
//   ck_assert_pstr_eq(s4, s2);
//   if (s2) free(s2);
// }
// END_TEST

START_TEST(test_insert_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_4) {
  char s1[30] = "abcdefghij";
  char s3[] = "\'I WAS HERE\'";
  char s4[] = "abc\'I WAS HERE\'defghij";
  s21_size_t num = 3;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

// START_TEST(test_insert_5) {
//   char s1[30] = "abc";
//   char s3[] = "333";
//   char *s4 = S21_NULL;
//   s21_size_t num = 10;
//   char *s2 = s21_insert(s1, s3, num);
//   ck_assert_pstr_eq(s4, s2);
//   if (s2) free(s2);
// }
// END_TEST

// START_TEST(test_insert_6) {
//   char s1[30] = "hello, world!";
//   char s3[] = "hELLO, WORLD!";
//   char *s4 = S21_NULL;
//   s21_size_t num = -1;
//   char *s2 = s21_insert(s1, s3, num);
//   ck_assert_pstr_eq(s4, s2);
//   if (s2) free(s2);
// }
// END_TEST

START_TEST(test_insert_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

// START_TEST(test_insert_9) {
//   char s1[] = "wtf";
//   char *s3 = S21_NULL;
//   char *s4 = S21_NULL;
//   s21_size_t num = 0;
//   char *s2 = s21_insert(s1, s3, num);
//   ck_assert_pstr_eq(s4, s2);
//   if (s2) free(s2);
// }
// END_TEST

// START_TEST(test_insert_10) {
//   char s1[] = "";
//   char *s3 = S21_NULL;
//   char *s4 = S21_NULL;
//   s21_size_t num = 0;
//   char *s2 = s21_insert(s1, s3, num);
//   ck_assert_pstr_eq(s2, s4);
//   if (s2) free(s2);
// }
// END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, insert_test1);
  tcase_add_test(tc, insert_test2);
  tcase_add_test(tc, insert_test3);
  tcase_add_test(tc, insert_test4);
  tcase_add_test(tc, insert_test5);
  tcase_add_test(tc, insert_str_null);
  tcase_add_test(tc, test_insert_1);
  // tcase_add_test(tc, test_insert_2);
  tcase_add_test(tc, test_insert_3);
  tcase_add_test(tc, test_insert_4);
  // tcase_add_test(tc, test_insert_5);
  // tcase_add_test(tc, test_insert_6);
  tcase_add_test(tc, test_insert_7);
  tcase_add_test(tc, test_insert_8);
  // tcase_add_test(tc, test_insert_9);
  // tcase_add_test(tc, test_insert_10);
  suite_add_tcase(s, tc);
  return s;
}
