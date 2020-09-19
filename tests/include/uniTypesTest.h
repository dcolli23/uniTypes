#include <units.h>
#include "gtest/gtest.h"

TEST(unitsTest, testKilogramInit){
  Mass test_var = 100_kg;
  ASSERT_EQ(test_var.getValue(), 100);
}

TEST(unitsTest, testLiterInit){
  Volume test_var = 123_l;
  ASSERT_EQ(test_var.getValue(), 123);
}