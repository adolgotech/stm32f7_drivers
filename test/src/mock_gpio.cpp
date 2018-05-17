#include <initializer_list>
#include "mock_gpio.hpp"
#include "stm32f7xx.h"

MockGpio::MockGpio(){

  for(auto port : {Port::A, Port::B, Port::C, Port::D, Port::E, Port::F,
                   Port::G, Port::H, Port::I, Port::J, Port::K}){
    setPortMode(port, 0x00000000);
    setPortOutputType(port, 0x0000);
  }
  setPortMode(Port::A, 0xA8000000);
  setPortMode(Port::B, 0x00000280);
}

MockGpio::~MockGpio(){}

uint32_t MockGpio::getPortMode(Port gPort){
  return portMode_[static_cast<uint8_t>(gPort)];
}

void MockGpio::setPortMode(Port gPort, uint32_t value){
  portMode_[static_cast<uint8_t>(gPort)] = value;
}

GpioMode MockGpio::getPinMode(Port gPort, Pin gPin){
  constexpr uint8_t pinMask = 0x3;
  uint8_t portVal = static_cast<uint8_t>(gPort);
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t portMode = getPortMode(gPort);
  // number of shifts is twice the pinVal
  uint8_t tempVal = (portMode >> (pinVal << 1)) & pinMask;
  GpioMode retVal;
  switch(tempVal){
    case 0:
      retVal = GpioMode::INPUT;
      break;

    case 1:
      retVal = GpioMode::GENERAL;
      break;

    case 2:
      retVal = GpioMode::ALTERNATE;
      break;

    case 3:
      retVal = GpioMode::ANALOG;
      break;
  }
  return retVal;
}

void MockGpio::setPinMode(Port gPort, Pin gPin, GpioMode gMode){
  // Validate value
  uint32_t tempValue = getPortMode(gPort);
  uint8_t pinValue = static_cast<uint8_t>(gPin);
  tempValue &= ~(3 << (pinValue << 1));
  tempValue |= (static_cast<uint8_t>(gMode) << (pinValue << 1));
  setPortMode(gPort, tempValue);
}

uint16_t MockGpio::getPortOutputType(Port gPort){
  return portOType_[static_cast<uint8_t>(gPort)];
}

void MockGpio::setPortOutputType(Port gPort, uint16_t value){
  portOType_[static_cast<uint8_t>(gPort)] = value;
}
