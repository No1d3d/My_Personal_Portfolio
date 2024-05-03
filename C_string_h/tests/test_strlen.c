#include "../tests_includes/s21_tests.h"

START_TEST(empty) {
  char src[] = "";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(abosal) {
  char src[] = "abosal";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(num) {
  char src[] = "987623456124678";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(string) {
  char src[] =
      "987623456124678qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(abosal_no_dal) {
  char src[] = "abosal\0no_dal";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(dai_mne_pen) {
  char src[] = "dai_mne_pen(321321)...123...123";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(Floppy_disk) {
  char src[] = "Floppy_disk";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(Russky_kot_Shlepa) {
  char src[] = "Russky_kot_Shlepa";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(kot_Vasily) {
  char src[] = "kot Vasily";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(floppa) {
  char src[] = "floppa";

  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_1) {
  char str[] = "Hello, world!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  char str[] =
      "213145346758697808-9704=3524-1309876289403-5=6576=432=-31044253=60931 "
      "21";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  char str[] = "Hello, world!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  char str[] = "\0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  char str[] =
      "I hate doing tests, it's not funny at all!!!!!!!!!!!!!!!!!!!!!!!!!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_6) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_7) {
  char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_8) {
  char str[] = "          00000000           ......  ";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_9) {
  char str[] = "\n\n\n\n\n\n\n\n\nlololol\n\n\n\n\n";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_10) {
  char str[] = "\0\0\0\0\n";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_11) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_12) {
  char str[] = "\t\t";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_13) {
  char str[] = "\0test";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_14) {
  char str[] = "wtf \0 wtf";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite *suite_strlen(void) {
  Suite *s = suite_create("suite_strlen");
  TCase *tc = tcase_create("strlen_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, abosal);
  tcase_add_test(tc, num);
  tcase_add_test(tc, string);
  tcase_add_test(tc, abosal_no_dal);
  tcase_add_test(tc, dai_mne_pen);
  tcase_add_test(tc, Floppy_disk);
  tcase_add_test(tc, floppa);
  tcase_add_test(tc, kot_Vasily);
  tcase_add_test(tc, Russky_kot_Shlepa);
  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_5);
  tcase_add_test(tc, strlen_6);
  tcase_add_test(tc, strlen_7);
  tcase_add_test(tc, strlen_8);
  tcase_add_test(tc, strlen_9);
  tcase_add_test(tc, strlen_10);
  tcase_add_test(tc, strlen_11);
  tcase_add_test(tc, strlen_12);
  tcase_add_test(tc, strlen_13);
  tcase_add_test(tc, strlen_14);

  suite_add_tcase(s, tc);
  return s;
}
