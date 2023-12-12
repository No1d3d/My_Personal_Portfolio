#include <gtest/gtest.h>

#include <stack>

#include "tests.h"
// #include "../s21_containers/stack/stack.tpp"

TEST(stack, case1) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.size(), 0U);
  EXPECT_THROW(s21_stack_int.top(), std::logic_error);
  EXPECT_THROW(s21_stack_int.pop(), std::logic_error);

  EXPECT_EQ(s21_stack_double.size(), 0U);
  EXPECT_THROW(s21_stack_double.top(), std::logic_error);
  EXPECT_THROW(s21_stack_double.pop(), std::logic_error);

  EXPECT_EQ(s21_stack_string.size(), 0U);
  EXPECT_THROW(s21_stack_string.top(), std::logic_error);
  EXPECT_THROW(s21_stack_string.pop(), std::logic_error);
}

TEST(stack, case2) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_stack_int.size(), 5U);
  EXPECT_EQ(s21_stack_int.top(), 1);

  EXPECT_EQ(s21_stack_double.size(), 5U);
  EXPECT_EQ(s21_stack_double.top(), 1.1);

  EXPECT_EQ(s21_stack_string.size(), 5U);
  EXPECT_EQ(s21_stack_string.top(), "!!");
}

TEST(stack, case3) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 3};
  s21::stack<int> s21_stack_res_int(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 3);

  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case4) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int = s21_stack_ref_int;

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double = s21_stack_ref_double;

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string = s21_stack_ref_string;

  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case5) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int = std::move(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double = std::move(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string =
      std::move(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case6) {
  s21::stack<int> s21_stack_ref_int = {1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int;
  s21_stack_res_int = std::move(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double;
  s21_stack_res_double = std::move(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string;
  s21_stack_res_string = std::move(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case7) {
  int n = 1e1;
  s21::stack<int> st = {};
  std::stack<int> orig_st = {};
  for (int i = 0; i < n; i++) {
    st.push(i);
    orig_st.push(i);
  }
  EXPECT_EQ(st.size(), orig_st.size());
  st.pop();
  st.pop();
  orig_st.pop();
  orig_st.pop();
  EXPECT_EQ(st.size(), orig_st.size());
  int top = st.top();
  int orig_top = orig_st.top();
  EXPECT_EQ(top, orig_top);
}

TEST(stack_EMPTY, case1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_stack_int.empty(), 0);
  EXPECT_EQ(s21_stack_double.empty(), 0);
  EXPECT_EQ(s21_stack_string.empty(), 0);
}

TEST(stack_EMPTY, case2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.empty(), 1);
  EXPECT_EQ(s21_stack_double.empty(), 1);
  EXPECT_EQ(s21_stack_string.empty(), 1);
}

TEST(stack_SIZE, case1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_stack_int.size(), 5U);
  EXPECT_EQ(s21_stack_double.size(), 5U);
  EXPECT_EQ(s21_stack_string.size(), 5U);
}

TEST(stack_SIZE, case2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.size(), 0U);
  EXPECT_EQ(s21_stack_double.size(), 0U);
  EXPECT_EQ(s21_stack_string.size(), 0U);
}

TEST(stack_TOP, case1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_stack_int.top(), 1);
  EXPECT_EQ(s21_stack_double.top(), 1.1);
  EXPECT_EQ(s21_stack_string.top(), "!!");
}

TEST(stack_TOP, case2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_THROW(s21_stack_int.top(), std::logic_error);
  EXPECT_THROW(s21_stack_double.top(), std::logic_error);
  EXPECT_THROW(s21_stack_string.top(), std::logic_error);
}

TEST(stack_PUSH, case1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  s21_stack_int.push(255);
  s21_stack_double.push(255.0);
  s21_stack_string.push("255");

  EXPECT_EQ(s21_stack_int.top(), 255);
  EXPECT_EQ(s21_stack_double.top(), 255.0);
  EXPECT_EQ(s21_stack_string.top(), "255");
}

TEST(stack_PUSH, case2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  s21_stack_int.push(255);
  s21_stack_double.push(255.0);
  s21_stack_string.push("255");

  EXPECT_EQ(s21_stack_int.top(), 255);
  EXPECT_EQ(s21_stack_double.top(), 255.0);
  EXPECT_EQ(s21_stack_string.top(), "255");
}

TEST(stack_POP, case1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  s21_stack_int.pop();
  s21_stack_double.pop();
  s21_stack_string.pop();

  EXPECT_EQ(s21_stack_int.top(), 9);
  EXPECT_EQ(s21_stack_double.top(), 9.1);
  EXPECT_EQ(s21_stack_string.top(), "!");
}

TEST(stack_POP, case2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_THROW(s21_stack_int.pop(), std::logic_error);
  EXPECT_THROW(s21_stack_double.pop(), std::logic_error);
  EXPECT_THROW(s21_stack_string.pop(), std::logic_error);
}

TEST(stack_SWAP, case1) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int;

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double;

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string;

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack_SWAP, case2) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int{12, 13, 14};

  s21::stack<double> s21_stack_ref_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<double> s21_stack_res_double{13.0};

  s21::stack<std::string> s21_stack_ref_string{"Hello", ",", "world", "!",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string{"14", "15"};

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 3U);
  EXPECT_EQ(s21_stack_ref_int.top(), 14);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 1U);
  EXPECT_EQ(s21_stack_ref_double.top(), 13.0);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 1.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 2U);
  EXPECT_EQ(s21_stack_ref_string.top(), "15");
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case666) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::stack<std::string> s21_stack_string{"Hello", ",", "world", "!", "!!"};

  s21_stack_int.insert_many_front(2, 3, 4);
  s21_stack_double.insert_many_front(2.0, 3.0, 4.0);
  s21_stack_string.insert_many_front("a", "aa", "aaa");
  EXPECT_EQ(s21_stack_int.top(), 4);
  EXPECT_EQ(s21_stack_double.top(), 4.0);
  EXPECT_EQ(s21_stack_string.top(), "aaa");
  EXPECT_EQ(s21_stack_int.size(), 8U);
  EXPECT_EQ(s21_stack_double.size(), 8U);
  EXPECT_EQ(s21_stack_string.size(), 8U);
}
