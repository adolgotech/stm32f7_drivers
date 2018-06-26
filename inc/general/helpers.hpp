#include <limits>
using std::numeric_limits;
using namespace GPIO;

template<class regType, class enumType>
regType updateReg(regType regVal, Pin gPin, enumType enumVal){
  uint8_t pinValue = static_cast<uint8_t>(gPin);
  uint8_t shiftVal = pinValue;
  uint8_t mask = 0b01;
  if(numeric_limits<regType>::digits == 32) {
    shiftVal <<= 1;
    mask = 0b11;
  }
  regVal &= ~(mask << shiftVal);
  regVal |= (static_cast<uint8_t>(enumVal) << shiftVal);
  return regVal;
};
