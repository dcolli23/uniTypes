#include "gtest/gtest.h"

// Include all of the test files we want to run.

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}