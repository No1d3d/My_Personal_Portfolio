#include "../tests_includes/s21_tests.h"

// START_TEST(correct_token_string) {
//     char str1[] = "Aboba++Floppa_! Kotya====!Shleppa";
//     char str2[] = "Aboba++Floppa_! Kotya====!Shleppa";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST

START_TEST(strtok_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "!";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_2) {
  char s1[] = "";
  char s2[] = "";
  char s3[] = "";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_3) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "\0";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_4) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_5) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "Hello, world!";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_6) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] =
      "My name is Polina. I hate this, maybe I'm not supposed for this.";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_7) {
  char s1[] = "ABABABABABBABABABBABABABABABBA";
  char s2[] = "ABABABABABBABABABBABABABABABBA";
  char s3[] = "B";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_8) {
  char s1[] = "\0ABABABABABBABABABBABABABABABBA";
  char s2[] = "\0ABABABABABBABABABBABABABABABBA";
  char s3[] = "A";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_9) {
  char s1[] = "\0Hello, world!";
  char s2[] = "\0Hello, world!";
  char s3[] = "\0";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_10) {
  char s1[] = "\0Hello, world!";
  char s2[] = "\0Hello, world!";
  char s3[] = "";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_11) {
  char *s1 = S21_NULL;
  char *s2 = S21_NULL;
  char s3[] = "";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_12) {
  char s1[] = "tuz-tuz-tuz";
  char s2[] = "tuz-tuz-tuz";
  char s3[] = "z-tuz-tuz";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(strtok_13) {
  char s1[] = "Hello, world! And other people";
  char s2[] = "Hello, world! And other people";
  char s3[] = "\0Come here";
  char s4[] = "\0Come here";
  char s5[] = "";

  ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
  for (int i = 0; i < 5; i++) {
    ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  }
  ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
}
END_TEST

START_TEST(strtok_14) {
  char s1[] = "Hello,       world! And other people";
  char s2[] = "Hello,       world! And other people";
  char s3[] = "Come here";
  char s4[] = "Come here";
  char s5[] = " o";

  ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
  for (int i = 0; i < 5; i++) {
    ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  }
  ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
}
END_TEST

START_TEST(strtok_15) {
  char s1[] = "Hello,      worllllllllllld! And lother people      ";
  char s2[] = "Hello,      worllllllllllld! And lother people      ";
  char s3[] = "Come here";
  char s4[] = "Come here";
  char s5[] = " l";

  ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
  for (int i = 0; i < 5; i++) {
    ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  }
  ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
  ck_assert_pstr_eq(strtok(S21_NULL, s5), s21_strtok(S21_NULL, s5));
}
END_TEST

// START_TEST(strtok_16) {
//   char s1[] = "Helllllllo,      worllllllllllld! And lother people      ";
//   char s2[] = "Helllllllo,      worllllllllllld! And lother people      ";
//   char s3[] = "Come here";
//   char s4[] = "Come here";
//   char s5[] = "l";
//   char s6[] = " ";
//     char s7[] = " ";
//
//   ck_assert_str_eq(strtok(s1, s5), s21_strtok(s2, s5));
//  // for (int i = 0; i < 5; i++) {
//     ck_assert_pstr_eq(strtok(S21_NULL, s6), s21_strtok(S21_NULL, s7));
//  // }
//   ck_assert_pstr_eq(strtok(s3, s6), s21_strtok(s4, s6));
//   ck_assert_pstr_eq(strtok(S21_NULL, s6), s21_strtok(S21_NULL, s6));
//   ck_assert_pstr_eq(strtok(S21_NULL, s6), s21_strtok(S21_NULL, s6));
// }
// END_TEST

START_TEST(strtok_17) {
  char s1[] = "ROROROROMA!!!!!!!!!";
  char s2[] = "ROROROROMA!!!!!!!!!";
  char s3[] = "R";
  strtok(s1, s3);
  strtok(NULL, s3);
  s21_strtok(s2, s3);
  s21_strtok(NULL, s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(strtok_18) {
  char s1[] = "AGONIA";
  char s2[] = "AGONIA";
  char s3[] = "A";
  strtok(s1, s3);
  strtok(NULL, s3);
  strtok(NULL, s3);
  s21_strtok(s2, s3);
  s21_strtok(NULL, s3);
  s21_strtok(NULL, s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(strtok_19) {
  char s1[] = "MYPHONENUM68697317172648";
  char s2[] = "MYPHONENUM68697317172648";
  char s3[] = "MYPHONENUM6869";
  char *s4 = strtok(s1, s3);
  char *s6 = strtok(S21_NULL, s3);

  char *s5 = s21_strtok(s2, s3);
  char *s7 = s21_strtok(S21_NULL, s3);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_pstr_eq(s4, s5);
  ck_assert_pstr_eq(s6, s7);
}
END_TEST

START_TEST(strtok_20) {
  char s1[] = "AAAAAAGOONIAAAAA";
  char s2[] = "AAAAAAGOONIAAAAA";
  char s3[] = "A";
  strtok(s1, s3);
  strtok(NULL, s2);
  strtok(NULL, s2);
  s21_strtok(s2, s3);
  s21_strtok(NULL, s3);
  s21_strtok(NULL, s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST
// START_TEST(hard_token_string) {
//     char str1[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
//     char str2[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
// START_TEST(unary_delimiters) {
//     char str1[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
//     char str2[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
// START_TEST(no_delims) {
//     char str1[] = "AbobaHasNoDelims";
//     char str2[] = "AbobaHasNoDelims";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST

START_TEST(only_delims) {
  char str1[] = "++++++++";
  char str2[] = "++++++++";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_ptr_null(got);
  ck_assert_ptr_null(expected);
}
END_TEST

// START_TEST(too_many_uses_non_segfault) {
//     char str1[] = "Aboba_Floppa_Roba";
//     char str2[] = "Aboba_Floppa_Roba";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     int i = 5;
//     while (i) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//         i--;
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
// START_TEST(even_n_of_delims) {
//     char str1[] = "Roba++++Kepa++A++++B__V";
//     char str2[] = "Roba++++Kepa++A++++B__V";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST

// START_TEST(odd_n_of_delims) {
//     char str1[] = "Aboba__+Floppa_  Roba";
//     char str2[] = "Aboba__+Floppa_  Roba";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
// START_TEST(mixed_n_of_delims) {
//     char str1[] = "Aboba__Floppa_+++Roba_Kepa";
//     char str2[] = "Aboba__Floppa_+++Roba_Kepa";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got && expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST

// START_TEST(hard_mixed) {
//     char str1[] = "     Aboba__+ Flo!ppa_   Roba+";
//     char str2[] = "     Aboba__+ Flo!ppa_   Roba+";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got || expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
// START_TEST(mixed_hard_incorrect) {
//     char str1[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
//     char str2[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
//     const char delims[] = "+_! =";
//
//     char *got = s21_strtok(str1, delims);
//     char *expected = strtok(str2, delims);
//
//     ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//     ck_assert_str_eq(got, expected);
//
//     while (got || expected) {
//         got = s21_strtok(NULL, delims);
//         expected = strtok(NULL, delims);
//
//         ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
//
//         if (got || expected) {
//             ck_assert_str_eq(got, expected);
//         } else {
//             ck_assert_ptr_null(got);
//             ck_assert_ptr_null(expected);
//         }
//     }
// } END_TEST
//
START_TEST(very_hard_mixed) {
  char str1[] = "!       A!B!C!D!E!!F!!G";
  char str2[] = "!       A!B!C!D!E!!F!!G";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got || expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    if (got || expected) {
      ck_assert_str_eq(got, expected);
      ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("suite_strtok");
  TCase *tc = tcase_create("strtok_tc");

  // tcase_add_test(tc, correct_token_string);
  // tcase_add_test(tc, hard_token_string);
  tcase_add_test(tc, strtok_1);
  tcase_add_test(tc, strtok_2);
  tcase_add_test(tc, strtok_3);
  tcase_add_test(tc, strtok_4);
  tcase_add_test(tc, strtok_5);
  tcase_add_test(tc, strtok_6);
  tcase_add_test(tc, strtok_7);
  tcase_add_test(tc, strtok_8);
  tcase_add_test(tc, strtok_9);
  tcase_add_test(tc, strtok_10);
  tcase_add_test(tc, strtok_11);
  tcase_add_test(tc, strtok_12);
  tcase_add_test(tc, strtok_13);
  tcase_add_test(tc, strtok_14);
  tcase_add_test(tc, strtok_15);
  // tcase_add_test(tc, strtok_16);
  tcase_add_test(tc, strtok_17);
  tcase_add_test(tc, strtok_18);
  tcase_add_test(tc, strtok_19);
  tcase_add_test(tc, strtok_20);

  tcase_add_test(tc, only_delims);
  //   tcase_add_test(tc, even_n_of_delims);
  //  tcase_add_test(tc, odd_n_of_delims);
  //    tcase_add_test(tc, mixed_n_of_delims);
  //    tcase_add_test(tc, too_many_uses_non_segfault);
  //    tcase_add_test(tc, hard_mixed);
  //    tcase_add_test(tc, mixed_hard_incorrect);
  tcase_add_test(tc, very_hard_mixed);
  //    tcase_add_test(tc, unary_delimiters);
  //    tcase_add_test(tc, no_delims);

  suite_add_tcase(s, tc);
  return s;
}
