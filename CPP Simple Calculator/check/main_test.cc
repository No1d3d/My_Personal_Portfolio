#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  // ::testing::GTEST_FLAG(filter) = "*TestGetRpn106*";
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}