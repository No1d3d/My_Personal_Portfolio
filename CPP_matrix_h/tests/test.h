#ifndef CPP1_S21_MATRIXPLUS_TESTS_TEST_H_
#define CPP1_S21_MATRIXPLUS_TESTS_TEST_H_

#define _GTEST_TIMEOUT 1

#include <gtest/gtest.h>

#include "./../s21_matrix/s21_matrix.h"
#include "./classes/test_helper.h"

#if (_GTEST_TIMEOUT == 1)
#define TEST_TIMEOUT_BEGIN if (1) {
#define TEST_TIMEOUT_END }
#else
#define TEST_TIMEOUT_BEGIN if (0) {
#define TEST_TIMEOUT_END }
#endif

#endif  // CPP1_S21_MATRIXPLUS_TESTS_TEST_H_
