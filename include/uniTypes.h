#pragma once
#include <ratio>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

namespace uniTypes {
  class RatioBaseClass {

  };

  // This should not be instantiated directly! Instead use the typedefs below.
  template<typename MassDim, typename LengthDim>
  class RatioQuantity : public RatioBaseClass {
  public:
    RatioQuantity() : value(0.0) {}
    RatioQuantity(double val) : value(val) {}

    RatioQuantity& operator+=(RatioQuantity& rhs){
      value += rhs.value;
      return *this;
    }

    RatioQuantity& operator-=(RatioQuantity& rhs){
      value -= rhs.value;
      return *this;
    }

    // Return value of the quantity in multiples of the specified unit.
    double convertTo(RatioQuantity& rhs) {
      return value / rhs.value;
    }

    // Returns the raw value of the quantity.
    double getValue(){
      return value;
    }

  private:
    double value;
  };

  // Specify the predefined physical quantity types.
  #define QUANTITY_TYPE(_Mdim, _Ldim, name) \
    typedef RatioQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>> name;

  // Dimensionless.
  QUANTITY_TYPE(0, 0, Number);

  QUANTITY_TYPE(1, 0, Mass);
  QUANTITY_TYPE(0, 1, Length);
  QUANTITY_TYPE(0, 2, Area);
  QUANTITY_TYPE(0, 3, Volume);

  // Standard arithmentic operators.
  template<typename M, typename L>
  RatioQuantity<M, L> operator+(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
    return RatioQuantity<M, L>(lhs.getValue() + rhs.getValue());
  }

  template<typename M, typename L>
  RatioQuantity<M, L> operator-(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
    return RatioQuantity<M, L>(lhs.getValue() - rhs.getValue());
  }

  template<typename M, typename L>
  RatioQuantity<M, L> operator*(double lhs, RatioQuantity<M, L>& rhs){
    return RatioQuantity<M, L>(lhs * rhs.getValue());
  }

  template<typename M, typename L>
  RatioQuantity<M, L> operator*(RatioQuantity<M, L>& lhs, double rhs){
    return RatioQuantity<M, L>(lhs.getValue() * rhs);
  }

  template<typename M1, typename L1, typename M2, typename L2>
  RatioQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>> 
    operator* (RatioQuantity<M1, L1>& lhs, RatioQuantity<M2, L2>& rhs) {
      return RatioQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>>(
        lhs.getValue() * rhs.getValue()
      );
  }

  template<typename M1, typename L1, typename M2, typename L2>
  RatioQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>> 
    operator/ (RatioQuantity<M1, L1>& lhs, RatioQuantity<M2, L2>& rhs) {
      return RatioQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>>(
        lhs.getValue() / rhs.getValue()
      );
  }

  template <typename M, typename L>
  RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>> 
    operator/(double x, RatioQuantity<M, L>& rhs) {
      return RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, 
                          std::ratio_subtract<std::ratio<0>, L>> (x / rhs.getValue());
  }

  template<typename M, typename L>
  RatioQuantity<M, L> operator/(RatioQuantity<M, L>& lhs, double x) {
    return RatioQuantity<M, L>(lhs.getValue() / x);
  }

  // Comparison operators.

  // This isn't working great with larger numbers since this is a simple double comparison.
  template<typename M, typename L>
  bool operator==(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
    return (lhs.getValue() == rhs.getValue());
  }

  template<typename M, typename L>
  bool operator!=(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
    return (lhs.getValue() != rhs.getValue());
  }

  template<typename M, typename L>
  bool operator<=(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
    return (lhs.getValue() <= rhs.getValue());
  }

  template<typename M, typename L>
  bool operator>=(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
    return (lhs.getValue() >= rhs.getValue());
  }

  template<typename M, typename L>
  bool operator<(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
    return (lhs.getValue() < rhs.getValue());
  }

  template<typename M, typename L>
  bool operator>(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
    return (lhs.getValue() > rhs.getValue());
  }

  // Our predefined mass units.
  Mass kilogram(1.0);
  Mass gram = 0.001 * kilogram;
  Mass milligram = 0.001 * gram;
  Mass ton = 1000.0 * kilogram;
  Mass ounce = 0.028349523125 * kilogram;
  Mass pound = 16 * ounce;
  Mass stone = 14 * pound;

  // Our predefined length units.
  Length meter(1.0);
  Length decimeter = meter / 10.0;
  Length centimeter = meter / 100.0;
  Length millimeter = meter / 1000.0;
  Length kilometer = meter * 1000.0;
  Length inch = 2.54 * centimeter;
  Length foot = 12.0 * inch;
  Length yard = 3.0 * foot;
  Length mile = 5280.0 * foot;

  // Our predefined area units.
  Area kilometer2 = kilometer * kilometer;
  Area meter2 = meter * meter;
  Area decimeter2 = decimeter * decimeter;
  Area centimeter2 = centimeter * centimeter;
  Area millimeter2 = millimeter * millimeter;
  Area inch2 = inch * inch;
  Area foot2 = foot * foot;
  Area yard2 = yard * yard;
  Area mile2 = mile * mile;

  // Our predefined volume units.
  Volume kilometer3 = kilometer2 * kilometer;
  Volume meter3 = meter2 * meter;
  Volume decimeter3 = decimeter2 * decimeter;
  Volume centimeter3 = centimeter2 * centimeter;
  Volume milliliter = centimeter3;
  Volume liter = 1000.0 * milliliter;
  Volume millimeter3 = millimeter2 * millimeter;
  Volume inch3 = inch2 * inch;
  Volume foot3 = foot2 * foot;
  Volume yard3 = yard2 * yard;
  Volume mile3 = mile2 * mile;
  Volume gallon = 3.78541 * liter;
  Volume quart = gallon / 4.0;
  Volume cup = quart / 2.0;
  Volume floz = cup / 8.0;
  Volume tablespoon = cup / 16.0;
  Volume teaspoon = tablespoon / 3.0;

  // Unit string literals
  namespace string_literals{
    // Length literals.
    Length operator"" _m(long double x) { return static_cast<double>(x) * meter; }
    Length operator"" _dm(long double x) { return static_cast<double>(x) * decimeter; }
    Length operator"" _cm(long double x) { return static_cast<double>(x) * centimeter; }
    Length operator"" _mm(long double x){ return static_cast<double>(x) * millimeter; }
    Length operator"" _km(long double x){ return static_cast<double>(x) * kilometer; }
    Length operator"" _in(long double x){ return static_cast<double>(x) * inch; }
    Length operator"" _ft(long double x){ return static_cast<double>(x) * foot; }
    Length operator"" _yd(long double x){ return static_cast<double>(x) * yard; }
    Length operator"" _mi(long double x){ return static_cast<double>(x) * mile; }
    Length operator"" _m(unsigned long long int x) { return static_cast<double>(x) * meter; }
    Length operator"" _dm(unsigned long long int x) { return static_cast<double>(x) * decimeter; }
    Length operator"" _cm(unsigned long long int x) { return static_cast<double>(x) * centimeter; }
    Length operator"" _mm(unsigned long long int x){ return static_cast<double>(x) * millimeter; }
    Length operator"" _km(unsigned long long int x){ return static_cast<double>(x) * kilometer; }
    Length operator"" _in(unsigned long long int x){ return static_cast<double>(x) * inch; }
    Length operator"" _ft(unsigned long long int x){ return static_cast<double>(x) * foot; }
    Length operator"" _yd(unsigned long long int x){ return static_cast<double>(x) * yard; }
    Length operator"" _mi(unsigned long long int x){ return static_cast<double>(x) * mile; }

    // Mass literals.
    Mass operator"" _kg(long double x){ return static_cast<double>(x) * kilogram; }
    Mass operator"" _g(long double x){ return static_cast<double>(x) * gram; }
    Mass operator"" _mg(long double x){ return static_cast<double>(x) * milligram; }
    Mass operator"" _tn(long double x){ return static_cast<double>(x) * ton; }
    Mass operator"" _oz(long double x){ return static_cast<double>(x) * ounce; }
    Mass operator"" _lb(long double x){ return static_cast<double>(x) * pound; }
    Mass operator"" _kg(unsigned long long int x){ return static_cast<double>(x) * kilogram; }
    Mass operator"" _g(unsigned long long int x){ return static_cast<double>(x) * gram; }
    Mass operator"" _mg(unsigned long long int x){ return static_cast<double>(x) * milligram; }
    Mass operator"" _tn(unsigned long long int x){ return static_cast<double>(x) * ton; }
    Mass operator"" _oz(unsigned long long int x){ return static_cast<double>(x) * ounce; }
    Mass operator"" _lb(unsigned long long int x){ return static_cast<double>(x) * pound; }

    // Volume literals.
    Volume operator "" _ml(long double x){ return static_cast<double>(x) * milliliter; }
    Volume operator "" _liter(long double x){ return static_cast<double>(x) * liter; }
    Volume operator "" _gal(long double x){ return static_cast<double>(x) * gallon; }
    Volume operator "" _qt(long double x){ return static_cast<double>(x) * quart; }
    Volume operator "" _cup(long double x){ return static_cast<double>(x) * cup; }
    Volume operator "" _fl(long double x){ return static_cast<double>(x) * floz; }
    Volume operator "" _tbsp(long double x){ return static_cast<double>(x) * tablespoon; }
    Volume operator "" _tsp(long double x){ return static_cast<double>(x) * teaspoon; }
    Volume operator "" _ml(unsigned long long int x){ return static_cast<double>(x) * milliliter; }
    Volume operator "" _liter(unsigned long long int x){ return static_cast<double>(x) * liter; }
    Volume operator "" _gal(unsigned long long int x){ return static_cast<double>(x) * gallon; }
    Volume operator "" _qt(unsigned long long int x){ return static_cast<double>(x) * quart; }
    Volume operator "" _cup(unsigned long long int x){ return static_cast<double>(x) * cup; }
    Volume operator "" _fl(unsigned long long int x){ return static_cast<double>(x) * floz; }
    Volume operator "" _tbsp(unsigned long long int x){ return static_cast<double>(x) * tablespoon; }
    Volume operator "" _tsp(unsigned long long int x){ return static_cast<double>(x) * teaspoon; }
  }

  // Create maps for mapping string to uniTypes type.
  
  using mass_map_t = std::map<std::string, uniTypes::Mass>;
  static const mass_map_t string_to_mass_unit{
    {"kilogram", uniTypes::kilogram}, {"kg", uniTypes::kilogram},
    {"gram", uniTypes::gram}, {"g", uniTypes::gram},
    {"milligram", uniTypes::milligram}, {"mg", uniTypes::milligram},
    {"ton", uniTypes::ton}, {"tn", uniTypes::ton},
    {"ounce", uniTypes::ounce}, {"oz", uniTypes::ounce},
    {"pound", uniTypes::pound}, {"lb", uniTypes::pound},
  };

  using volume_map_t = std::map<std::string, uniTypes::Volume>;
  static const volume_map_t string_to_volume_unit{
    {"milliliter", uniTypes::milliliter}, {"ml", uniTypes::milliliter},
    {"liter", uniTypes::liter}, {"l", uniTypes::liter},
    {"gallon", uniTypes::gallon}, {"gal", uniTypes::gallon},
    {"quart", uniTypes::quart}, {"qt", uniTypes::quart},
    {"cup", uniTypes::cup}, {"c", uniTypes::cup},
    {"fluid ounce", uniTypes::floz}, {"floz", uniTypes::floz}, {"fl", uniTypes::floz},
    {"tablespoon", uniTypes::tablespoon}, {"tbsp", uniTypes::tablespoon},
    {"teaspoon", uniTypes::teaspoon}, {"tsp", uniTypes::teaspoon}
  };
  
  // TODO: Add streaming functions that print out unit by finding unit that leads to least amount of
  // significant digits.

}
