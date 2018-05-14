#include <initializer_list>
#include <type_traits>
#include "mock_gpio.hpp"
#include "stm32f7xx.h"
using std::is_enum;
MockGpio::MockGpio(){
  setPortMode(Port::A, 0xA8000000);
  setPortMode(Port::B, 0x00000280);
  for(auto port : {Port::C, Port::D, Port::E, Port::F,
                   Port::G, Port::H, Port::I, Port::J, Port::K}){
    setPortMode(port, 0x00000000);
  }
}

MockGpio::~MockGpio(){}

uint32_t MockGpio::getPortMode(Port gPort){
  uint32_t retVal = 0;
  // if(is_enum<gPort>::value){
    retVal = portMode_[static_cast<uint8_t>(gPort)];
  // }
  return retVal;
}

void MockGpio::setPortMode(Port gPort, uint32_t value){
  // if(is_enum<gPort>::value){
    portMode_[static_cast<uint8_t>(gPort)] = value;
  // }
}

uint8_t MockGpio::getPinMode(Port gPort, Pin gPin){
  constexpr uint8_t pinMask = 0x3;
  uint8_t portVal = static_cast<uint8_t>(gPort);
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t portMode = getPortMode(gPort);
  // number of shifts is twice the pinVal
  return static_cast<uint8_t>((portMode >> (pinVal << 1)) & pinMask);
}

void MockGpio::setPinMode(Port gPort, Pin gPin, uint8_t value){
  // Validate value
  if(value <= 0x3) {
    uint32_t tempValue = getPortMode(gPort);
    uint8_t pinValue = static_cast<uint8_t>(gPin);
    tempValue &= (0 << (pinValue << 1));
    tempValue |= (value << (pinValue << 1));
    setPortMode(gPort, tempValue);
  }
}
// uint32_t MockGpio::getPortAMode(){
//   return 0xA8000000;
// }
//
// uint32_t MockGpio::getPortBMode(){
//   return 0x00000280;
// }
// MockGpio::setMode(uint32_t mode){
//
// }
