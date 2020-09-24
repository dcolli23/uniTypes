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
  template<typename MassDim, typename LengthDim, typename TimeDim>
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
  #define QUANTITY_TYPE(_Mdim, _Ldim, _Tdim, name) \
    typedef RatioQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>> name;

  // Dimensionless.
  QUANTITY_TYPE(0, 0, 0, Number);

  QUANTITY_TYPE(1, 0, 0, Mass);
  QUANTITY_TYPE(0, 1, 0, Length);
  QUANTITY_TYPE(0, 2, 0, Area);
  QUANTITY_TYPE(0, 3, 0, Volume);
  QUANTITY_TYPE(0, 0, 1, Time);
  QUANTITY_TYPE(1, 1, -2, Force);
  QUANTITY_TYPE(2, 1, -2, Energy);

  // Standard arithmentic operators.
  template<typename M, typename L, typename T>
  RatioQuantity<M, L, T> operator+(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs){
    return RatioQuantity<M, L, T>(lhs.getValue() + rhs.getValue());
  }

  template<typename M, typename L, typename T>
  RatioQuantity<M, L, T> operator-(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs){
    return RatioQuantity<M, L, T>(lhs.getValue() - rhs.getValue());
  }

  template<typename M, typename L, typename T>
  RatioQuantity<M, L, T> operator*(double lhs, RatioQuantity<M, L, T>& rhs){
    return RatioQuantity<M, L, T>(lhs * rhs.getValue());
  }

  template<typename M, typename L, typename T>
  RatioQuantity<M, L, T> operator*(RatioQuantity<M, L, T>& lhs, double rhs){
    return RatioQuantity<M, L, T>(lhs.getValue() * rhs);
  }

  template<typename M1, typename L1, typename T1,
           typename M2, typename L2, typename T2>
  RatioQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>, std::ratio_add<T1, T2>> 
    operator* (RatioQuantity<M1, L1, T1>& lhs, RatioQuantity<M2, L2, T2>& rhs) {
      return RatioQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>, std::ratio_add<T1, T2>>(
        lhs.getValue() * rhs.getValue()
      );
  }

  template<typename M1, typename L1, typename T1,
           typename M2, typename L2, typename T2>
  RatioQuantity<std::ratio_subtract<M1, M2>, 
                std::ratio_subtract<L1, L2>, 
                std::ratio_subtract<T1, T2>> 
    operator/ (RatioQuantity<M1, L1, T1>& lhs, RatioQuantity<M2, L2, T2>& rhs) {
      return RatioQuantity<std::ratio_subtract<M1, M2>, 
                           std::ratio_subtract<L1, L2>,
                           std::ratio_subtract<T1, T2>>( lhs.getValue() / rhs.getValue() );
  }

  template <typename M, typename L, typename T>
  RatioQuantity<std::ratio_subtract<std::ratio<0>, M>,
                std::ratio_subtract<std::ratio<0>, L>,
                std::ratio_subtract<std::ratio<0>, T>> 
    operator/(double x, RatioQuantity<M, L, T>& rhs) {
      return RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, 
                           std::ratio_subtract<std::ratio<0>, L>,
                           std::ratio_subtract<std::ratio<0>, T>> ( x / rhs.getValue() );
  }

  template<typename M, typename L, typename T>
  RatioQuantity<M, L, T> operator/(RatioQuantity<M, L, T>& lhs, double x) {
    return RatioQuantity<M, L, T>( lhs.getValue() / x );
  }

  // Comparison operators.

  // This isn't working great with larger numbers since this is a simple double comparison.
  template<typename M, typename L, typename T>
  bool operator==(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs){
    return (lhs.getValue() == rhs.getValue());
  }

  template<typename M, typename L, typename T>
  bool operator!=(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs) {
    return (lhs.getValue() != rhs.getValue());
  }

  template<typename M, typename L, typename T>
  bool operator<=(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs) {
    return (lhs.getValue() <= rhs.getValue());
  }

  template<typename M, typename L, typename T>
  bool operator>=(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs) {
    return (lhs.getValue() >= rhs.getValue());
  }

  template<typename M, typename L, typename T>
  bool operator<(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs) {
    return (lhs.getValue() < rhs.getValue());
  }

  template<typename M, typename L, typename T>
  bool operator>(RatioQuantity<M, L, T>& lhs, RatioQuantity<M, L, T>& rhs) {
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

  Time second(1.0);
  Time minute = 60.0 * second;
  Time hour = 60.0 * minute;
  Time day = 24.0 * hour;
  Time week = 7.0 * day;
  Time year = 365.25 * day;
  Time millisecond = second / 1000.0;
  Time microsecond = millisecond / 1000.0;
  Time nanosecond = microsecond / 1000.0;

  Force newton(1.0);
  Force kilonewton = 1000.0 * newton;
  Force meganewton = 1000.0 * kilonewton;
  Force millinewton = newton / 1000.0;
  Force poundforce = newton * 4.44822271072093;

  Energy joule(1.0);
  Energy kilojoule = 1000.0 * joule;
  Energy megajoule = 1000.0 * kilojoule;
  Energy kilocalorie = 4184.0 * joule;
  Energy btu = 1055.06 * joule;

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
  
    Time operator "" _s(long double x){ return static_cast<double>(x) * second; }
    Time operator "" _min(long double x) { return static_cast<double>(x) * minute; }
    Time operator "" _hr(long double x) { return static_cast<double>(x) * hour; }
    Time operator "" _day(long double x) { return static_cast<double>(x) * day; }
    Time operator "" _week(long double x) { return static_cast<double>(x) * week; }
    Time operator "" _year(long double x) { return static_cast<double>(x) * year; }
    Time operator "" _ms(long double x) { return static_cast<double>(x) * millisecond; }
    Time operator "" _ns(long double x) { return static_cast<double>(x) * nanosecond; }
    Time operator "" _s(unsigned long long int x){ return static_cast<double>(x) * second; }
    Time operator "" _min(unsigned long long int x) { return static_cast<double>(x) * minute; }
    Time operator "" _hr(unsigned long long int x) { return static_cast<double>(x) * hour; }
    Time operator "" _day(unsigned long long int x) { return static_cast<double>(x) * day; }
    Time operator "" _week(unsigned long long int x) { return static_cast<double>(x) * week; }
    Time operator "" _year(unsigned long long int x) { return static_cast<double>(x) * year; }
    Time operator "" _ms(unsigned long long int x) { return static_cast<double>(x) * millisecond; }
    Time operator "" _ns(unsigned long long int x) { return static_cast<double>(x) * nanosecond; }

    Force operator "" _N(long double x){ return static_cast<double>(x) * newton; }
    Force operator "" _kN(long double x){ return static_cast<double>(x) * kilonewton; }
    Force operator "" _MN(long double x){ return static_cast<double>(x) * meganewton; }
    Force operator "" _mN(long double x){ return static_cast<double>(x) * millinewton; }
    Force operator "" _lbf(long double x){ return static_cast<double>(x) * poundforce; }
    Force operator "" _N(unsigned long long int x){ return static_cast<double>(x) * newton; }
    Force operator "" _kN(unsigned long long int x){ return static_cast<double>(x) * kilonewton; }
    Force operator "" _MN(unsigned long long int x){ return static_cast<double>(x) * meganewton; }
    Force operator "" _mN(unsigned long long int x){ return static_cast<double>(x) * millinewton; }
    Force operator "" _lbf(unsigned long long int x){ return static_cast<double>(x) * poundforce; }

    Energy operator "" _J(long double x){ return static_cast<double>(x) * joule; }
    Energy operator "" _kJ(long double x){ return static_cast<double>(x) * kilojoule; }
    Energy operator "" _MJ(long double x){ return static_cast<double>(x) * megajoule; }
    Energy operator "" _kcal(long double x){ return static_cast<double>(x) * kilocalorie; }
    Energy operator "" _btu(long double x){ return static_cast<double>(x) * btu; }
    Energy operator "" _J(unsigned long long int x){ return static_cast<double>(x) * joule; }
    Energy operator "" _kJ(unsigned long long int x){ return static_cast<double>(x) * kilojoule; }
    Energy operator "" _MJ(unsigned long long int x){ return static_cast<double>(x) * megajoule; }
    Energy operator "" _kcal(unsigned long long int x){ return static_cast<double>(x)
      * kilocalorie; }
    Energy operator "" _btu(unsigned long long int x){ return static_cast<double>(x) * btu;}
  }

  // Create maps for mapping string to uniTypes type.
  
  using mass_map_t = std::map<std::string, Mass>;
  static const mass_map_t string_to_mass_unit{
    {"kilogram", kilogram}, {"kg", kilogram},
    {"gram", gram}, {"g", gram},
    {"milligram", milligram}, {"mg", milligram},
    {"ton", ton}, {"tn", ton},
    {"ounce", ounce}, {"oz", ounce},
    {"pound", pound}, {"lb", pound},
  };

  using volume_map_t = std::map<std::string, Volume>;
  static const volume_map_t string_to_volume_unit{
    {"milliliter", milliliter}, {"ml", milliliter},
    {"liter", liter}, {"l", liter},
    {"gallon", gallon}, {"gal", gallon},
    {"quart", quart}, {"qt", quart},
    {"cup", cup}, {"c", cup},
    {"fluid ounce", floz}, {"floz", floz}, {"fl", floz},
    {"tablespoon", tablespoon}, {"tbsp", tablespoon},
    {"teaspoon", teaspoon}, {"tsp", teaspoon}
  };

  using length_map_t = std::map<std::string, Length>;
  static const length_map_t string_to_length_unit{
    {"meter", meter}, {"m", meter},
    {"decimeter", decimeter}, {"dm", decimeter},
    {"centimeter", centimeter}, {"cm", centimeter},
    {"millimeter", millimeter}, {"mm", millimeter},
    {"kilometer", kilometer}, {"km", kilometer},
    {"inch", inch}, {"in", inch},
    {"foot", foot}, {"ft", foot},
    {"yard", yard}, {"yd", yard},
    {"mile", mile}, {"mi", mile}
  };
  
  // TODO: Add streaming functions that print out unit by finding unit that leads to least amount of
  // significant digits.

}
