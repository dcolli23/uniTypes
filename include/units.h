#include <ratio>

// This should not be instantiated directly! Instead use the typedefs below.
template<typename MassDim, typename LengthDim>
class RatioQuantity {
public:
  constexpr RatioQuantity() : value(0.0) {}
  constexpr RatioQuantity(double val) : value(val) {}

  constexpr RatioQuantity const& operator+=(const RatioQuantity& rhs){
    value += rhs.value;
    return *this;
  }

  constexpr RatioQuantity const& operator-=(const RatioQuantity& rhs){
    value -= rhs.value;
    return *this;
  }

  // Return value of the quantity in multiples of the specified unit.
  constexpr double Convert(const RatioQuantity& rhs) {
    return value / rhs.value();
  }

  // Returns the raw value of the quantity.
  constexpr double getValue(){
    return value;
  }

private:
  double value;
};

// Specify the predefined physical quantity types.
#define QUANTITY_TYPE(_Mdim, _Ldim, name) \
  typdef RatioQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>> name;

// Dimensionless.
QUANTITY_TYPE(0, 0, Number);

QUANTITY_TYPE(1, 0, QMass);
QUANTITY_TYPE(0, 1, QLength);
QUANTITY_TYPE(0, 3, QVolume);

// Standard arithmentic operators.
template<typename M, typename L>
RatioQuantity<M, L> operator+(RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
  return RatioQuantity<M, L>(lhs.getValue + rhs.getValue());
}

template<typename M, typename L>
RatioQuantity<M, L> operator-(const RatioQuantity<M, L>& lhs, RatioQuantity<M, L>& rhs){
  return RatioQuantity<M, L>(lhs.getValue() - rhs.getValue());
}

template<typename M, typename L>
RatioQuantity<M, L> operator*(double lhs, RatioQuantity<M, L>& rhs){
  return RatioQuantity<M, L>(lhs * rhs.getValue());
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
  operator* (RatioQuantity<M1, L1>& lhs, RatioQuantity<M2, L2>& rhs) {
    return RatioQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>>(
      lhs.getValue() / rhs.getValue()
    );
}

template <typename M, typename L>
RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>> 
  operator/(double x, const RatioQuantity<M, L>& rhs) {
    return RatioQuantity<std::ratio_subtract<std::ratio<0>, M>, 
                         std::ratio_subtract<std::ratio<0>, L>> (x / rhs.getValue());
}
