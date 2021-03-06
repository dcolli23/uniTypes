#include <uniTypes.h>
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <map>

// For using the string literal operators.
using namespace uniTypes::string_literals;

TEST(uniTypesTest, testKilogramInit){
  uniTypes::Mass test_var = 100_kg;
  double num_kg_test = test_var.convertTo(uniTypes::kilogram);
  EXPECT_FLOAT_EQ(num_kg_test, 100);
}

TEST(uniTypesTest, testLiterInit){
  uniTypes::Volume test_var = 123_liter;
  double num_liters_test = test_var.convertTo(uniTypes::liter);
  EXPECT_FLOAT_EQ(num_liters_test, 123);
}

TEST(uniTypesTest, CupToFlozTest) {
  uniTypes::Volume test_var = 64_cup;
  double num_floz_test = test_var.convertTo(uniTypes::floz);
  double num_floz_truth = 64.0 * 8.0;
  EXPECT_FLOAT_EQ(num_floz_test, num_floz_truth);
}

TEST(uniTypesTest, GallonQuartConversionTest) {
  uniTypes::Volume test_var = 25_gal;
  double num_quarts_test = test_var.convertTo(uniTypes::quart);
  EXPECT_FLOAT_EQ(num_quarts_test, 100);
}

TEST(uniTypesTest, SecondInitTest) {
  uniTypes::Time test_var = 60.0_s;
  double num_seconds_test = test_var.convertTo(uniTypes::second);
  EXPECT_FLOAT_EQ(num_seconds_test, 60.0);
}

TEST(uniTypesTest, KCalInitTest) {
  uniTypes::Energy test_var = 256.0_kcal;
  double num_kcal_test = test_var.convertTo(uniTypes::kilocalorie);
  EXPECT_FLOAT_EQ(num_kcal_test, 256.0);
}

TEST(uniTypesTest, NewtonInitTest) {
  uniTypes::Force test_var = 10.0_N;
  double num_newton_test = test_var.convertTo(uniTypes::newton);
  EXPECT_FLOAT_EQ(num_newton_test, 10.0);
}

TEST(uniTypesTest, IUInitTest) {
  uniTypes::UOBA test_var = 135.5_IU;
  double num_iu_test = test_var.convertTo(uniTypes::IU);
  EXPECT_FLOAT_EQ(num_iu_test, 135.5);
}

TEST(uniTypesTest, FactoryNumberInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(1, 12.5);
  uniTypes::Number truth_var = 12.5;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::kilogram), truth_var.convertTo(uniTypes::kilogram));
}

TEST(uniTypesTest, FactoryUOBAInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(2, 100.01);
  uniTypes::UOBA truth_var = 100.01_IU;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::IU), truth_var.convertTo(uniTypes::IU));
}

TEST(uniTypesTest, FactoryMassInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(3, 12.5);
  uniTypes::Mass truth_var = 12.5_kg;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::kilogram), truth_var.convertTo(uniTypes::kilogram));
}

TEST(uniTypesTest, FactoryLengthInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(4, 10.0);
  uniTypes::Length truth_var = 10.0_m;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::meter), truth_var.convertTo(uniTypes::meter));
}

TEST(uniTypesTest, FactoryAreaInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(5, 30.0);
  uniTypes::Area truth_var = 30.0 * uniTypes::meter2;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::meter2), truth_var.convertTo(uniTypes::meter2));
}

TEST(uniTypesTest, FactoryVolumeInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(6, 0.005);
  uniTypes::Volume truth_var = 0.005 * uniTypes::meter3;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::meter3), truth_var.convertTo(uniTypes::meter3));
}

TEST(uniTypesTest, FactoryTimeInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(7, 13.7);
  uniTypes::Time truth_var = 13.7_s;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::second), truth_var.convertTo(uniTypes::second));
}

TEST(uniTypesTest, FactoryForceInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(8, 9.81);
  uniTypes::Force truth_var = 9.81_N;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::newton), truth_var.convertTo(uniTypes::newton));
}

TEST(uniTypesTest, FactoryEnergyInitTest) {
  uniTypes::RatioBase* test_var = uniTypes::RatioBase::createRatio(9, 4.18);
  uniTypes::Energy truth_var = 4.18_J;
  EXPECT_FLOAT_EQ(test_var->convertTo(uniTypes::joule), truth_var.convertTo(uniTypes::joule));
}

TEST(uniTypesTest, MapStorageTest) {
  std::map<std::string, uniTypes::RatioBase*> unit_map;
  
  unit_map["mass"] = new uniTypes::Mass(13.5_g);
  unit_map["time"] = new uniTypes::Time(60.0_s);
  
  uniTypes::Mass mass_truth = 13.5_g;
  uniTypes::Time time_truth = 60.0_s;
  
  EXPECT_FLOAT_EQ(unit_map.at("mass")->convertTo(uniTypes::kilogram), mass_truth.convertTo(uniTypes::kilogram));
  EXPECT_FLOAT_EQ(unit_map.at("time")->convertTo(uniTypes::second), time_truth.convertTo(uniTypes::second));

  for (auto &it : unit_map) {
    delete it.second;
  }
}

TEST(uniTypesTest, AdditionTest) {
  uniTypes::Length test_var_1 = 10_m;
  uniTypes::Length test_var_2 = 25_m;
  uniTypes::Length test_var = test_var_1 + test_var_2;
  uniTypes::Length truth_var = 35_m;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::meter), truth_var.convertTo(uniTypes::meter));
}

TEST(uniTypesTest, SubtractionTest) {
  uniTypes::Mass test_var_1 = 35.3_lb;
  uniTypes::Mass test_var_2 = 0.3_lb;
  uniTypes::Mass test_var = test_var_1 - test_var_2;
  uniTypes::Mass truth_var = 35.0_lb;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::pound), truth_var.convertTo(uniTypes::pound));
}

TEST(uniTypesTest, MultiplicationTest) {
  uniTypes::Length test_var_1 = 10_cm;
  uniTypes::Area test_var = test_var_1 * test_var_1;
  uniTypes::Area truth_var = 100.0 * uniTypes::centimeter2;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::centimeter2), 
    truth_var.convertTo(uniTypes::centimeter2));
}

TEST(uniTypesTest, DoubleMultiplicationTest) {
  uniTypes::Area test_var_1 = 75.0 * uniTypes::inch2;
  uniTypes::Area test_var = test_var_1 / 3.0;
  uniTypes::Area truth_var = 25.0 * uniTypes::inch2;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::inch2), truth_var.convertTo(uniTypes::inch2));
}

TEST(uniTypesTest, DoubleMultiplicationReflexiveTest) {
  uniTypes::Area test_var_1 = uniTypes::inch2 * 75.0;
  uniTypes::Area test_var = test_var_1 / 3.0;
  uniTypes::Area truth_var = uniTypes::inch2 * 25.0;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::inch2), truth_var.convertTo(uniTypes::inch2));
}

TEST(uniTypesTest, DivisionTest) {
  uniTypes::Volume test_var_1 = 100.0 * uniTypes::meter3;
  uniTypes::Length test_var_2 = 50.0_m;
  uniTypes::Area test_var = test_var_1 / test_var_2;
  uniTypes::Area truth_var = 2.0 * uniTypes::meter2;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::meter2), truth_var.convertTo(uniTypes::meter2));
}

TEST(uniTypesTest, DivisionSameUnitTest) {
  uniTypes::Area test_var_1 = 100.0 * uniTypes::meter2;
  uniTypes::Area test_var_2 = 50.0 * uniTypes::meter2;
  double multiples_area = test_var_1 / test_var_2;
  EXPECT_FLOAT_EQ(multiples_area, 2.0);
}

TEST(uniTypesTest, DoubleDivisionTest) {
  uniTypes::Volume test_var_1 = 84_tbsp;
  uniTypes::Volume test_var = test_var_1 / 42.0;
  uniTypes::Volume truth_var = 2.0_tbsp;
  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::tablespoon), truth_var.convertTo(uniTypes::tablespoon));
}

// This isn't working great with larger numbers since this is a simple double comparison.
TEST(uniTypesTest, ComparisonTest) {
  uniTypes::Length test_var = 12.0_mi;
  uniTypes::Length truth_var = (12.0 * 5280.0) * uniTypes::foot;
  ASSERT_TRUE(test_var == truth_var);
}

TEST(uniTypesTypeMapTest, TypeMapMassTest) {
  uniTypes::Mass truth_var = 25.5_g;
  uniTypes::Mass test_unit = uniTypes::string_to_mass_unit.at("g");
  uniTypes::Mass test_var = 25.5 * test_unit;

  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::gram), truth_var.convertTo(uniTypes::gram));
}

TEST(uniTypesTypeMapTest, TypeMapVolumeTest) {
  uniTypes::Volume truth_var = 13.34_qt;
  uniTypes::Volume test_unit = uniTypes::string_to_volume_unit.at("quart");
  uniTypes::Volume test_var = 13.34 * test_unit;

  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::quart), truth_var.convertTo(uniTypes::quart));
}

TEST(uniTypesTypeMapTest, TypeMapLengthTest) {
  uniTypes::Length truth_var = 87.75_m;
  uniTypes::Length test_unit = uniTypes::string_to_length_unit.at("m");
  uniTypes::Length test_var = 87.75 * test_unit;

  EXPECT_FLOAT_EQ(test_var.convertTo(uniTypes::foot), truth_var.convertTo(uniTypes::foot));
}