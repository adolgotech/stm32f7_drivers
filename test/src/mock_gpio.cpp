#include <initializer_list>
#include "mock_gpio.hpp"
// #include "general/helpers.hpp"
using namespace GPIO;
MockGpio::MockGpio(GPIO_TypeDef *gpio, RCC_TypeDef *rcc) : Gpio(gpio, rcc), gpio_(gpio){}

MockGpio::~MockGpio(){}

uint32_t MockGpio::getMode(){
  return Gpio::getMode();
}

Mode MockGpio::getMode(Pin gPin){
  constexpr uint8_t pinMask = 0x3;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t portMode = getMode();
  // number of shifts is twice the pinVal
  uint8_t tempVal = (portMode >> (pinVal << 1)) & pinMask;
  return static_cast<Mode>(tempVal);
}

void MockGpio::setMode(uint32_t value){
  Gpio::setMode(value);
}

uint16_t MockGpio::getOutputType(){
  return Gpio::getOutputType();
}

OutputType MockGpio::getOutputType(Pin gPin){
  constexpr uint8_t pinMask = 1;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint16_t portOutputType = getOutputType();
  uint8_t tempVal = (portOutputType >> pinVal) & pinMask;
  return static_cast<OutputType>(tempVal);
}

void MockGpio::setOutputType(uint16_t value){
  Gpio::setOutputType(value);
}

uint32_t MockGpio::getOutputSpeed(){
  return Gpio::getOutputSpeed();
}

void MockGpio::setOutputSpeed(uint32_t value){
  Gpio::setOutputSpeed(value);
}

OutputSpeed MockGpio::getOutputSpeed(Pin gPin){
  constexpr uint8_t pinMask = 0x3;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t portSpeed = getOutputSpeed();
  // number of shifts is twice the pinVal
  uint8_t tempVal = (portSpeed >> (pinVal << 1)) & pinMask;
  return static_cast<OutputSpeed>(tempVal);
}

uint32_t MockGpio::getPull() {
  return Gpio::getPull();
}

Pull MockGpio::getPull(Pin gPin){
  constexpr uint8_t pinMask = 0x3;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t pull = getPull();
  // number of shifts is twice the pinVal
  uint8_t tempVal = (pull >> (pinVal << 1)) & pinMask;
  return static_cast<Pull>(tempVal);
}

void MockGpio::setPull(uint32_t value){
  Gpio::setPull(value);
}

uint16_t MockGpio::read(){
  return Gpio::read();
}

void MockGpio::write(uint16_t value){
  gpio_->IDR = value;
  Gpio::write(value);
}

void MockGpio::write(Pin gPin, Bit value){
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t data = 1 << pinVal;
  if(value == Bit::CLR){
    data <<= 16;
  }
  gpio_->BSRR = data;
  bitSetClear(data);
}

void MockGpio::bitSetClear(uint32_t value){
  uint16_t set = static_cast<uint16_t>(value & 0xffff);
  uint16_t clr = static_cast<uint16_t>((value >> 16) & 0xffff);
  uint16_t data = read();
  if(set != 0x0000){
    data |= set;
    write(data);
  } else if(clr != 0x0000){
    data &= ~clr;
    write(data);
  }
}

uint32_t MockGpio::getAlternateLow(){
  return Gpio::getAlternateLow();
}

uint32_t MockGpio::getAlternateHigh(){
  return Gpio::getAlternateHigh();
}

void MockGpio::setAlternateLow(uint32_t value){
  Gpio::setAlternateLow(value);
}

void MockGpio::setAlternateHigh(uint32_t value){
  Gpio::setAlternateHigh(value);
}

Alt MockGpio::getAlternate(Pin gPin){
  constexpr uint8_t pinMask = 0xf;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t alternate = 0;
  Alt retVal = Alt::AF0;
  if(pinVal < 8){
    alternate = getAlternateLow();
    retVal = static_cast<Alt>((alternate >> (4 * pinVal)) & pinMask);
  } else {
    alternate = getAlternateHigh();
    retVal = static_cast<Alt>((alternate >> (4 * (pinVal - 8))) & pinMask);
  }
  return retVal;
}
