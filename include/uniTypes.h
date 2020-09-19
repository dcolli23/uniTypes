#include <ratio>

// This should not be instantiated directly! Instead use the typedefs below.
template<typename MassDim, typename LengthDim>
class RatioQuantity {
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
  double Convert(RatioQuantity& rhs) {
    return value / rhs.value();
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

QUANTITY_TYPE(1, 0, QMass);
QUANTITY_TYPE(0, 1, QLength);
QUANTITY_TYPE(0, 2, QArea);
QUANTITY_TYPE(0, 3, QVolume);

// Standard arithmentic operators.
template<typename M, typename L>
RatioQuantity<M, L> operator+(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
  return RatioQuantity<M, L>(lhs.getValue + rhs.getValue());
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
bool operator<(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs) {
  return (lhs.getValue() < rhs.getValue());
}

// Our predefined mass units.
QMass kilogram(1.0);
QMass gram = 0.001 * kilogram;
QMass ton = 1000.0 * kilogram;
QMass ounce = 0.028349523125 * kilogram;
QMass pound = 16 * ounce;
QMass stone = 14 * pound;

// Our predefined length units.
QLength meter(1.0);
QLength decimeter = meter / 10.0;
QLength centimeter = meter / 100.0;
QLength millimeter = meter / 1000.0;
QLength kilometer = meter * 1000.0;
QLength inch = 2.54 * centimeter;
QLength foot = 12.0 * inch;
QLength yard = 3.0 * foot;
QLength mile = 5280.0 * foot;

// Our predefined area units.
QArea kilometer2 = kilometer * kilometer;
QArea meter2 = meter * meter;
QArea decimeter2 = decimeter * decimeter;
QArea centimeter2 = centimeter * centimeter;
QArea millimeter2 = millimeter * millimeter;
QArea inch2 = inch * inch;
QArea foot2 = foot * foot;
QArea yard2 = yard * yard;
QArea mile2 = mile * mile;

// Our predefined volume units.
QVolume kilometer3 = kilometer2 * kilometer;
QVolume meter3 = meter2 * meter;
QVolume decimeter3 = decimeter2 * decimeter;
QVolume centimeter3 = centimeter2 * centimeter;
QVolume milliliter = centimeter3;
QVolume liter = 1000.0 * milliliter;
QVolume millimeter3 = millimeter2 * millimeter;
QVolume inch3 = inch2 * inch;
QVolume foot3 = foot2 * foot;
QVolume yard3 = yard2 * yard;
QVolume mile3 = mile2 * mile;
QVolume gallon = 3.78541 * liter;
QVolume quart = gallon / 4.0;
QVolume cup = quart / 2.0;
QVolume floz = cup / 8.0;
QVolume tablespoon = cup / 16.0;
QVolume teaspoon = tablespoon / 3.0;

// Unit string literals

// Length literals.
QLength operator"" _m(long double x) { return static_cast<double>(x) * meter; }
QLength operator"" _dm(long double x) { return static_cast<double>(x) * decimeter; }
QLength operator"" _cm(long double x) { return static_cast<double>(x) * centimeter; }
QLength operator"" _mm(long double x){ return static_cast<double>(x) * millimeter; }
QLength operator"" _km(long double x){ return static_cast<double>(x) * kilometer; }
QLength operator"" _in(long double x){ return static_cast<double>(x) * inch; }
QLength operator"" _ft(long double x){ return static_cast<double>(x) * foot; }
QLength operator"" _yd(long double x){ return static_cast<double>(x) * yard; }
QLength operator"" _mi(long double x){ return static_cast<double>(x) * mile; }
QLength operator"" _m(unsigned long long int x) { return static_cast<double>(x) * meter; }
QLength operator"" _dm(unsigned long long int x) { return static_cast<double>(x) * decimeter; }
QLength operator"" _cm(unsigned long long int x) { return static_cast<double>(x) * centimeter; }
QLength operator"" _mm(unsigned long long int x){ return static_cast<double>(x) * millimeter; }
QLength operator"" _km(unsigned long long int x){ return static_cast<double>(x) * kilometer; }
QLength operator"" _in(unsigned long long int x){ return static_cast<double>(x) * inch; }
QLength operator"" _ft(unsigned long long int x){ return static_cast<double>(x) * foot; }
QLength operator"" _yd(unsigned long long int x){ return static_cast<double>(x) * yard; }
QLength operator"" _mi(unsigned long long int x){ return static_cast<double>(x) * mile; }

// Mass literals.
QMass operator"" _kg(long double x){ return static_cast<double>(x) * kilogram; }
QMass operator"" _g(long double x){ return static_cast<double>(x) * gram; }
QMass operator"" _tn(long double x){ return static_cast<double>(x) * ton; }
QMass operator"" _oz(long double x){ return static_cast<double>(x) * ounce; }
QMass operator"" _lb(long double x){ return static_cast<double>(x) * pound; }
QMass operator"" _kg(unsigned long long int x){ return static_cast<double>(x) * kilogram; }
QMass operator"" _g(unsigned long long int x){ return static_cast<double>(x) * gram; }
QMass operator"" _tn(unsigned long long int x){ return static_cast<double>(x) * ton; }
QMass operator"" _oz(unsigned long long int x){ return static_cast<double>(x) * ounce; }
QMass operator"" _lb(unsigned long long int x){ return static_cast<double>(x) * pound; }

// Volume literals.
QVolume operator "" _ml(long double x){ return static_cast<double>(x) * milliliter; }
QVolume operator "" _liter(long double x){ return static_cast<double>(x) * liter; }
QVolume operator "" _gal(long double x){ return static_cast<double>(x) * gallon; }
QVolume operator "" _qt(long double x){ return static_cast<double>(x) * quart; }
QVolume operator "" _cup(long double x){ return static_cast<double>(x) * cup; }
QVolume operator "" _fl(long double x){ return static_cast<double>(x) * floz; }
QVolume operator "" _tbsp(long double x){ return static_cast<double>(x) * tablespoon; }
QVolume operator "" _tsp(long double x){ return static_cast<double>(x) * teaspoon; }
QVolume operator "" _ml(unsigned long long int x){ return static_cast<double>(x) * milliliter; }
QVolume operator "" _liter(unsigned long long int x){ return static_cast<double>(x) * liter; }
QVolume operator "" _gal(unsigned long long int x){ return static_cast<double>(x) * gallon; }
QVolume operator "" _qt(unsigned long long int x){ return static_cast<double>(x) * quart; }
QVolume operator "" _cup(unsigned long long int x){ return static_cast<double>(x) * cup; }
QVolume operator "" _fl(unsigned long long int x){ return static_cast<double>(x) * floz; }
QVolume operator "" _tbsp(unsigned long long int x){ return static_cast<double>(x) * tablespoon; }
QVolume operator "" _tsp(unsigned long long int x){ return static_cast<double>(x) * teaspoon; }

