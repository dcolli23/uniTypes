#include <uniTypes.h>
#include "gtest/gtest.h"

#include <iostream>

// For using the string literal operators.
using namespace uniTypes::string_literals;

double ERROR_TOLERANCE = 1e-10;

TEST(uniTypesTest, testKilogramInit){
  uniTypes::Mass test_var = 100_kg;
  double num_kg_test = test_var.convertTo(uniTypes::kilogram);
  ASSERT_NEAR(num_kg_test, 100, ERROR_TOLERANCE);
}

TEST(uniTypesTest, testLiterInit){
  uniTypes::Volume test_var = 123_liter;
  double num_liters_test = test_var.convertTo(uniTypes::liter);
  ASSERT_NEAR(num_liters_test, 123, ERROR_TOLERANCE);
}

TEST(uniTypesTest, CupToFlozTest) {
  uniTypes::Volume test_var = 64_cup;
  double num_floz_test = test_var.convertTo(uniTypes::floz);
  double num_floz_truth = 64.0 * 8.0;
  ASSERT_NEAR(num_floz_test, num_floz_truth, ERROR_TOLERANCE);
}

TEST(uniTypesTest, GallonQuartConversionTest) {
  uniTypes::Volume test_var = 25_gal;
  double num_quarts_test = test_var.convertTo(uniTypes::quart);
  ASSERT_NEAR(num_quarts_test, 100, ERROR_TOLERANCE);
}

TEST(uniTypesTest, AdditionTest) {
  uniTypes::Length test_var_1 = 10_m;
  uniTypes::Length test_var_2 = 25_m;
  uniTypes::Length test_var = test_var_1 + test_var_2;
  uniTypes::Length truth_var = 35_m;
  ASSERT_NEAR(test_var.convertTo(uniTypes::meter), truth_var.convertTo(uniTypes::meter), 
    ERROR_TOLERANCE);
}

TEST(uniTypesTest, SubtractionTest) {
  uniTypes::Mass test_var_1 = 35.3_lb;
  uniTypes::Mass test_var_2 = 0.3_lb;
  uniTypes::Mass test_var = test_var_1 - test_var_2;
  uniTypes::Mass truth_var = 35.0_lb;
  ASSERT_NEAR(test_var.convertTo(uniTypes::pound), truth_var.convertTo(uniTypes::pound), 
    ERROR_TOLERANCE);
}

TEST(uniTypesTest, MultiplicationTest) {
  uniTypes::Length test_var_1 = 10_cm;
  uniTypes::Area test_var = test_var_1 * test_var_1;
  uniTypes::Area truth_var = 100.0 * uniTypes::centimeter2;
  ASSERT_NEAR(test_var.convertTo(uniTypes::centimeter2), 
    truth_var.convertTo(uniTypes::centimeter2), ERROR_TOLERANCE);
}

TEST(uniTypesTest, DoubleMultiplicationTest) {
  uniTypes::Area test_var_1 = 75.0 * uniTypes::inch2;
  uniTypes::Area test_var = test_var_1 / 3.0;
  uniTypes::Area truth_var = 25.0 * uniTypes::inch2;
  ASSERT_NEAR(test_var.convertTo(uniTypes::inch2), truth_var.convertTo(uniTypes::inch2),
    ERROR_TOLERANCE);
}

TEST(uniTypesTest, DivisionTest) {
  uniTypes::Volume test_var_1 = 100.0 * uniTypes::meter3;
  uniTypes::Length test_var_2 = 50.0_m;
  uniTypes::Area test_var = test_var_1 / test_var_2;
  uniTypes::Area truth_var = 2.0 * uniTypes::meter2;
  ASSERT_NEAR(test_var.convertTo(uniTypes::meter2), truth_var.convertTo(uniTypes::meter2),
    ERROR_TOLERANCE);
}

TEST(uniTypesTest, DoubleDivisionTest) {
  uniTypes::Volume test_var_1 = 84_tbsp;
  uniTypes::Volume test_var = test_var_1 / 42.0;
  uniTypes::Volume truth_var = 2.0_tbsp;
  ASSERT_NEAR(test_var.convertTo(uniTypes::tablespoon), truth_var.convertTo(uniTypes::tablespoon),
    ERROR_TOLERANCE);
}

// This isn't working great with larger numbers since this is a simple double comparison.
TEST(uniTypesTest, ComparisonTest) {
  uniTypes::Length test_var = 12.0_mi;
  uniTypes::Length truth_var = (12.0 * 5280.0) * uniTypes::foot;
  ASSERT_TRUE(test_var == truth_var);
}

TEST(uniTypesTest, WrongUnitAdditionTest) {
  uniTypes::Length length_var = 12.0_mi;
  uniTypes::Volume volume_var = 1.0_gal;
  length_var += volume_var;
}

// TEST(uniTypesTypeMapTest, TypeMapMassTest) {
//   uniTypes::Mass test_var = 25.5_g;
//   uniTypes::type_maps::type_map["g"] = 25.5 * uniTypes::type_maps::mass_unit_map["g"]
// }