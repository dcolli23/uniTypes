#pragma once
#include <ratio>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

namespace uniTypes {
  class RatioBase {
  public:
    RatioBase() : value(0.0) {};
    RatioBase(double val) : value(val) {};
    virtual ~RatioBase() {};
    static RatioBase* createRatio(int choice, double val);
    virtual double convertTo(RatioBase) {};

    double value;
  };
  
  // This should not be instantiated directly! Instead use the typedefs below.
  template<typename MassDim, typename LengthDim, typename TimeDim>
  class RatioQuantity : public RatioBase {
  public:
    RatioQuantity() : RatioBase(0.0) {}
    RatioQuantity(double val) : RatioBase(val) {}
    
    // Copy constructor
    RatioQuantity(const RatioQuantity<MassDim, LengthDim, TimeDim> &rat)
    {
      this->value = rat.value;
    }
    
    virtual ~RatioQuantity(){};

    RatioQuantity operator+=(RatioQuantity rhs){
      value += rhs.value;
      return *this;
    }

    RatioQuantity operator-=(RatioQuantity rhs){
      value -= rhs.value;
      return *this;
    }

    // Return value of the quantity in multiples of the specified unit.
    double convertTo(RatioBase rhs) override {
      return value / rhs.value;
    }

    // Returns the raw value of the quantity.
    double getValue(){
      return value;
    }

  // private:
    // double value;
  };

  // Specify the predefined physical quantity types.
  #define QUANTITY_TYPE(_Mdim, _Ldim, _Tdim, name) \
    typedef RatioQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>> name;

  // Dimensionless.
  QUANTITY_TYPE(0, 0, 0, Number);

  // International Unit. Standardized unit of biological activity. No direct conversion to mass so
  // it is therefore defined as dimensionless.
  // UOBA stands for "unit of biological activity" here.
  QUANTITY_TYPE(0, 0, 0, UOBA);

  QUANTITY_TYPE(1, 0, 0, Mass);
  QUANTITY_TYPE(0, 1, 0, Length);
  QUANTITY_TYPE(0, 2, 0, Area);
  QUANTITY_TYPE(0, 3, 0, Volume);
  QUANTITY_TYPE(0, 0, 1, Time);
  QUANTITY_TYPE(1, 1, -2, Force);
  QUANTITY_TYPE(2, 1, -2, Energy);

  // ------------------------------------------
  // RatioBase::createRatio
  // ------------------------------------------
  // Factory method for creating derived RatioQuantity from base class.
  // int choice:
  //    + 1 - Number
  //    + 2 - UOBA
  //    + 3 - Mass
  //    + 4 - Length
  //    + 5 - Area
  //    + 6 - Volume
  //    + 7 - Time
  //    + 8 - Force
  //    + 9 - Energy
  // double val = 0.0, Value that derived class constructed with.
  RatioBase* RatioBase::createRatio(int choice, double val=0.0) {
    switch(choice) {
      case 1: return new Number(val);
      case 2: return new UOBA(val);
      case 3: return new Mass(val);
      case 4: return new Length(val);
      case 5: return new Area(val);
      case 6: return new Volume(val);
      case 7: return new Time(val);
      case 8: return new Force(val);
      case 9: return new Energy(val);
    }
  }

  // Standard arithmentic operators.
  template<typename M, typename L, typename T>
  inline RatioQuantity<M, L, T> operator+(RatioQuantity<M, L, T> lhs, 
                                          RatioQuantity<M, L, T> rhs)
  {
    return RatioQuantity<M, L, T>(lhs.getValue() + rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline RatioQuantity<M, L, T> operator-(RatioQuantity<M, L, T> lhs, 
                                          RatioQuantity<M, L, T> rhs)
  {
    return RatioQuantity<M, L, T>(lhs.getValue() - rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline RatioQuantity<M, L, T> operator*(double lhs, 
                                          RatioQuantity<M, L, T> rhs)
  {
    return RatioQuantity<M, L, T>(lhs * rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline RatioQuantity<M, L, T> operator*(RatioQuantity<M, L, T> lhs, 
                                          double rhs)
  {
    return RatioQuantity<M, L, T>(lhs.getValue() * rhs);
  }

  template<typename M1, typename L1, typename T1,
           typename M2, typename L2, typename T2>
  inline RatioQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>, std::ratio_add<T1, T2>> 
    operator* (RatioQuantity<M1, L1, T1> lhs, RatioQuantity<M2, L2, T2> rhs) 
  {
      return RatioQuantity<std::ratio_add<M1, M2>, 
                           std::ratio_add<L1, L2>, 
                           std::ratio_add<T1, T2>> ( lhs.getValue() * rhs.getValue() );
  }

  template<typename M, typename L, typename T>
  inline double operator/(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) {
    return lhs.getValue() / rhs.getValue();
  }

  template<typename M1, typename L1, typename T1,
           typename M2, typename L2, typename T2>
  inline RatioQuantity<std::ratio_subtract<M1, M2>, 
                       std::ratio_subtract<L1, L2>, 
                       std::ratio_subtract<T1, T2>> 
    operator/ (RatioQuantity<M1, L1, T1> lhs, RatioQuantity<M2, L2, T2> rhs) 
  {
      return RatioQuantity<std::ratio_subtract<M1, M2>, 
                           std::ratio_subtract<L1, L2>,
                           std::ratio_subtract<T1, T2>>( lhs.getValue() / rhs.getValue() );
  }

  template <typename M, typename L, typename T>
  inline RatioQuantity<std::ratio_subtract<std::ratio<0>, M>,
                       std::ratio_subtract<std::ratio<0>, L>,
                       std::ratio_subtract<std::ratio<0>, T>> 
    operator/(double x, RatioQuantity<M, L, T> rhs) 
  {
      return RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, 
                           std::ratio_subtract<std::ratio<0>, L>,
                           std::ratio_subtract<std::ratio<0>, T>> ( x / rhs.getValue() );
  }

  template<typename M, typename L, typename T>
  inline RatioQuantity<M, L, T> operator/(RatioQuantity<M, L, T> lhs, double x) 
  {
    return RatioQuantity<M, L, T>( lhs.getValue() / x );
  }

  // Comparison operators.

  // This isn't working great with larger numbers since this is a simple double comparison.
  template<typename M, typename L, typename T>
  inline bool operator==(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs)
  {
    return (lhs.getValue() == rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline bool operator!=(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) 
  {
    return (lhs.getValue() != rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline bool operator<=(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) 
  {
    return (lhs.getValue() <= rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline bool operator>=(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) 
  {
    return (lhs.getValue() >= rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline bool operator<(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) 
  {
    return (lhs.getValue() < rhs.getValue());
  }

  template<typename M, typename L, typename T>
  inline bool operator>(RatioQuantity<M, L, T> lhs, RatioQuantity<M, L, T> rhs) 
  {
    return (lhs.getValue() > rhs.getValue());
  }

  // International Units.
  static inline UOBA IU(1.0);

  // Our predefined mass units.
  static inline Mass kilogram(1.0);
  static inline Mass gram = 0.001 * kilogram;
  static inline Mass milligram = 0.001 * gram;
  static inline Mass ton = 1000.0 * kilogram;
  static inline Mass ounce = 0.028349523125 * kilogram;
  static inline Mass pound = 16 * ounce;
  static inline Mass stone = 14 * pound;

  // Our predefined length units.
  static inline Length meter(1.0);
  static inline Length decimeter = meter / 10.0;
  static inline Length centimeter = meter / 100.0;
  static inline Length millimeter = meter / 1000.0;
  static inline Length kilometer = meter * 1000.0;
  static inline Length inch = 2.54 * centimeter;
  static inline Length foot = 12.0 * inch;
  static inline Length yard = 3.0 * foot;
  static inline Length mile = 5280.0 * foot;

  // Our predefined area units.
  static inline Area kilometer2 = kilometer * kilometer;
  static inline Area meter2 = meter * meter;
  static inline Area decimeter2 = decimeter * decimeter;
  static inline Area centimeter2 = centimeter * centimeter;
  static inline Area millimeter2 = millimeter * millimeter;
  static inline Area inch2 = inch * inch;
  static inline Area foot2 = foot * foot;
  static inline Area yard2 = yard * yard;
  static inline Area mile2 = mile * mile;

  // Our predefined volume units.
  static inline Volume kilometer3 = kilometer2 * kilometer;
  static inline Volume meter3 = meter2 * meter;
  static inline Volume decimeter3 = decimeter2 * decimeter;
  static inline Volume centimeter3 = centimeter2 * centimeter;
  static inline Volume milliliter = centimeter3;
  static inline Volume liter = 1000.0 * milliliter;
  static inline Volume millimeter3 = millimeter2 * millimeter;
  static inline Volume inch3 = inch2 * inch;
  static inline Volume foot3 = foot2 * foot;
  static inline Volume yard3 = yard2 * yard;
  static inline Volume mile3 = mile2 * mile;
  static inline Volume gallon = 3.78541 * liter;
  static inline Volume quart = gallon / 4.0;
  static inline Volume cup = quart / 2.0;
  static inline Volume floz = cup / 8.0;
  static inline Volume tablespoon = cup / 16.0;
  static inline Volume teaspoon = tablespoon / 3.0;

  static inline Time second(1.0);
  static inline Time minute = 60.0 * second;
  static inline Time hour = 60.0 * minute;
  static inline Time day = 24.0 * hour;
  static inline Time week = 7.0 * day;
  static inline Time year = 365.25 * day;
  static inline Time millisecond = second / 1000.0;
  static inline Time microsecond = millisecond / 1000.0;
  static inline Time nanosecond = microsecond / 1000.0;

  static inline Force newton(1.0);
  static inline Force kilonewton = 1000.0 * newton;
  static inline Force meganewton = 1000.0 * kilonewton;
  static inline Force millinewton = newton / 1000.0;
  static inline Force poundforce = newton * 4.44822271072093;

  static inline Energy joule(1.0);
  static inline Energy kilojoule = 1000.0 * joule;
  static inline Energy megajoule = 1000.0 * kilojoule;
  static inline Energy kilocalorie = 4184.0 * joule;
  static inline Energy btu = 1055.06 * joule;

  // Unit string literals
  namespace string_literals{
    // IU literals.
    inline UOBA operator "" _IU(long double x) { return static_cast<double>(x) * IU; }
    inline UOBA operator "" _IU(unsigned long long int x) { return static_cast<double>(x) * IU; }

    // Length literals.
    inline Length operator"" _m(long double x) { return static_cast<double>(x) * meter; }
    inline Length operator"" _dm(long double x) { return static_cast<double>(x) * decimeter; }
    inline Length operator"" _cm(long double x) { return static_cast<double>(x) * centimeter; }
    inline Length operator"" _mm(long double x) { return static_cast<double>(x) * millimeter; }
    inline Length operator"" _km(long double x) { return static_cast<double>(x) * kilometer; }
    inline Length operator"" _in(long double x) { return static_cast<double>(x) * inch; }
    inline Length operator"" _ft(long double x) { return static_cast<double>(x) * foot; }
    inline Length operator"" _yd(long double x) { return static_cast<double>(x) * yard; }
    inline Length operator"" _mi(long double x) { return static_cast<double>(x) * mile; }
    inline Length operator"" _m(unsigned long long int x) { return static_cast<double>(x) * meter; }
    inline Length operator"" _dm(unsigned long long int x) { return static_cast<double>(x) * decimeter; }
    inline Length operator"" _cm(unsigned long long int x) { return static_cast<double>(x) * centimeter; }
    inline Length operator"" _mm(unsigned long long int x) { return static_cast<double>(x) * millimeter; }
    inline Length operator"" _km(unsigned long long int x) { return static_cast<double>(x) * kilometer; }
    inline Length operator"" _in(unsigned long long int x) { return static_cast<double>(x) * inch; }
    inline Length operator"" _ft(unsigned long long int x) { return static_cast<double>(x) * foot; }
    inline Length operator"" _yd(unsigned long long int x) { return static_cast<double>(x) * yard; }
    inline Length operator"" _mi(unsigned long long int x) { return static_cast<double>(x) * mile; }

    // Mass literals.
    inline Mass operator"" _kg(long double x) { return static_cast<double>(x) * kilogram; }
    inline Mass operator"" _g(long double x) { return static_cast<double>(x) * gram; }
    inline Mass operator"" _mg(long double x) { return static_cast<double>(x) * milligram; }
    inline Mass operator"" _tn(long double x) { return static_cast<double>(x) * ton; }
    inline Mass operator"" _oz(long double x) { return static_cast<double>(x) * ounce; }
    inline Mass operator"" _lb(long double x) { return static_cast<double>(x) * pound; }
    inline Mass operator"" _kg(unsigned long long int x) { return static_cast<double>(x) * kilogram; }
    inline Mass operator"" _g(unsigned long long int x) { return static_cast<double>(x) * gram; }
    inline Mass operator"" _mg(unsigned long long int x) { return static_cast<double>(x) * milligram; }
    inline Mass operator"" _tn(unsigned long long int x) { return static_cast<double>(x) * ton; }
    inline Mass operator"" _oz(unsigned long long int x) { return static_cast<double>(x) * ounce; }
    inline Mass operator"" _lb(unsigned long long int x) { return static_cast<double>(x) * pound; }

    // Volume literals.
    inline Volume operator "" _ml(long double x) { return static_cast<double>(x) * milliliter; }
    inline Volume operator "" _liter(long double x) { return static_cast<double>(x) * liter; }
    inline Volume operator "" _gal(long double x) { return static_cast<double>(x) * gallon; }
    inline Volume operator "" _qt(long double x) { return static_cast<double>(x) * quart; }
    inline Volume operator "" _cup(long double x) { return static_cast<double>(x) * cup; }
    inline Volume operator "" _fl(long double x) { return static_cast<double>(x) * floz; }
    inline Volume operator "" _tbsp(long double x) { return static_cast<double>(x) * tablespoon; }
    inline Volume operator "" _tsp(long double x) { return static_cast<double>(x) * teaspoon; }
    inline Volume operator "" _ml(unsigned long long int x) { return static_cast<double>(x) * milliliter; }
    inline Volume operator "" _liter(unsigned long long int x) { return static_cast<double>(x) * liter; }
    inline Volume operator "" _gal(unsigned long long int x) { return static_cast<double>(x) * gallon; }
    inline Volume operator "" _qt(unsigned long long int x) { return static_cast<double>(x) * quart; }
    inline Volume operator "" _cup(unsigned long long int x) { return static_cast<double>(x) * cup; }
    inline Volume operator "" _fl(unsigned long long int x) { return static_cast<double>(x) * floz; }
    inline Volume operator "" _tbsp(unsigned long long int x) { return static_cast<double>(x) * tablespoon; }
    inline Volume operator "" _tsp(unsigned long long int x) { return static_cast<double>(x) * teaspoon; }
  
    inline Time operator "" _s(long double x) { return static_cast<double>(x) * second; }
    inline Time operator "" _min(long double x) { return static_cast<double>(x) * minute; }
    inline Time operator "" _hr(long double x) { return static_cast<double>(x) * hour; }
    inline Time operator "" _day(long double x) { return static_cast<double>(x) * day; }
    inline Time operator "" _week(long double x) { return static_cast<double>(x) * week; }
    inline Time operator "" _year(long double x) { return static_cast<double>(x) * year; }
    inline Time operator "" _ms(long double x) { return static_cast<double>(x) * millisecond; }
    inline Time operator "" _ns(long double x) { return static_cast<double>(x) * nanosecond; }
    inline Time operator "" _s(unsigned long long int x) { return static_cast<double>(x) * second; }
    inline Time operator "" _min(unsigned long long int x) { return static_cast<double>(x) * minute; }
    inline Time operator "" _hr(unsigned long long int x) { return static_cast<double>(x) * hour; }
    inline Time operator "" _day(unsigned long long int x) { return static_cast<double>(x) * day; }
    inline Time operator "" _week(unsigned long long int x) { return static_cast<double>(x) * week; }
    inline Time operator "" _year(unsigned long long int x) { return static_cast<double>(x) * year; }
    inline Time operator "" _ms(unsigned long long int x) { return static_cast<double>(x) * millisecond; }
    inline Time operator "" _ns(unsigned long long int x) { return static_cast<double>(x) * nanosecond; }

    inline Force operator "" _N(long double x) { return static_cast<double>(x) * newton; }
    inline Force operator "" _kN(long double x) { return static_cast<double>(x) * kilonewton; }
    inline Force operator "" _MN(long double x) { return static_cast<double>(x) * meganewton; }
    inline Force operator "" _mN(long double x) { return static_cast<double>(x) * millinewton; }
    inline Force operator "" _lbf(long double x) { return static_cast<double>(x) * poundforce; }
    inline Force operator "" _N(unsigned long long int x) { return static_cast<double>(x) * newton; }
    inline Force operator "" _kN(unsigned long long int x) { return static_cast<double>(x) * kilonewton; }
    inline Force operator "" _MN(unsigned long long int x) { return static_cast<double>(x) * meganewton; }
    inline Force operator "" _mN(unsigned long long int x) { return static_cast<double>(x) * millinewton; }
    inline Force operator "" _lbf(unsigned long long int x) { return static_cast<double>(x) * poundforce; }

    inline Energy operator "" _J(long double x) { return static_cast<double>(x) * joule; }
    inline Energy operator "" _kJ(long double x) { return static_cast<double>(x) * kilojoule; }
    inline Energy operator "" _MJ(long double x) { return static_cast<double>(x) * megajoule; }
    inline Energy operator "" _kcal(long double x) { return static_cast<double>(x) * kilocalorie; }
    inline Energy operator "" _btu(long double x) { return static_cast<double>(x) * btu; }
    inline Energy operator "" _J(unsigned long long int x) { return static_cast<double>(x) * joule; }
    inline Energy operator "" _kJ(unsigned long long int x) { return static_cast<double>(x) * kilojoule; }
    inline Energy operator "" _MJ(unsigned long long int x) { return static_cast<double>(x) * megajoule; }
    inline Energy operator "" _kcal(unsigned long long int x) { return static_cast<double>(x)
      * kilocalorie; }
    inline Energy operator "" _btu(unsigned long long int x) { return static_cast<double>(x) * btu;}
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
