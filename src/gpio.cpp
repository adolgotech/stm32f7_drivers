#include "gpio.hpp"
using namespace GPIO;

Gpio::Gpio(GPIO_TypeDef *gpio, RCC_TypeDef *rcc) : GpioInterface(), gpio_(gpio){
  // Initialize GPIO clock
  if(gpio_ == GPIOA){
    rcc->AHB1ENR |= 1l;
  } else if(gpio_ == GPIOB){
    rcc->AHB1ENR |= 2l;
  } else if(gpio_ == GPIOC){
    rcc->AHB1ENR |= 4l;
  } else if(gpio_ == GPIOD){
    rcc->AHB1ENR |= 8l;
  } else if(gpio_ == GPIOE){
    rcc->AHB1ENR |= 16l;
  } else if(gpio_ == GPIOF){
    rcc->AHB1ENR |= 32l;
  } else if(gpio_ == GPIOG){
    rcc->AHB1ENR |= 64l;
  } else if(gpio_ == GPIOH){
    rcc->AHB1ENR |= 128l;
  } else if(gpio_ == GPIOI){
    rcc->AHB1ENR |= 256l;
  } else if(gpio_ == GPIOJ){
    rcc->AHB1ENR |= 512l;
  } else if(gpio_ == GPIOK){
    rcc->AHB1ENR |= 1024l;
  }
}

void Gpio::setMode(Pin gPin, Mode gMode){
  uint32_t tempValue = getMode();
  setMode(updateReg<uint32_t, Mode>(tempValue, gPin, gMode));
}

void Gpio::setOutputType(Pin gPin, OutputType gOutputType){
  uint16_t tempValue = getOutputType();
  setOutputType(updateReg<uint16_t, OutputType>(tempValue, gPin, gOutputType));
}

void Gpio::setOutputSpeed(Pin gPin, OutputSpeed gOutputSpeed){
  uint32_t tempValue = getOutputSpeed();
  setOutputSpeed(updateReg<uint32_t, OutputSpeed>(tempValue, gPin, gOutputSpeed));
}

void Gpio::setPull(Pin gPin, Pull gPull){
  uint32_t tempValue = getPull();
  setPull(updateReg<uint32_t, Pull>(tempValue, gPin, gPull));
}

Bit Gpio::read(Pin gPin){
  constexpr uint8_t pinMask = 0x1;
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint16_t data = read();
  uint8_t tempVal = (data >> pinVal) & pinMask;
  return static_cast<Bit>(tempVal);
}

void Gpio::write(Pin gPin, Bit value){
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t data = 1 << pinVal;
  if(value == Bit::CLR){
    data <<= 16;
  }
  gpio_->BSRR = data;
}

void Gpio::setAlternate(Pin gPin, Alt gAlt){
  uint8_t pinVal = static_cast<uint8_t>(gPin);
  uint32_t alternate = 0;
  if(pinVal < 8){
    alternate = getAlternateLow();
    alternate &= ~(0xf << (4 * pinVal));
    alternate |= ((static_cast<uint8_t>(gAlt) & 0xf) << (4 * pinVal));
    setAlternateLow(alternate);
  } else {
    alternate = getAlternateHigh();
    alternate &= ~(0xf << (4 * (pinVal - 8)));
    alternate |= ((static_cast<uint8_t>(gAlt) & 0xf) << (4 * (pinVal - 8)));
    setAlternateHigh(alternate);
  }
}

void Gpio::toggle(Pin gPin){
  Bit tempVal = read(gPin);
  if(tempVal == Bit::CLR){
    write(gPin, Bit::SET);
  } else {
    write(gPin, Bit::CLR);
  }
}
