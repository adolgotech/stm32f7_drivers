#pragma once
#include "stm32f7xx.h"
#include "gpio_interface.hpp"
namespace GPIO {
class Gpio: public GpioInterface {
  public:
    Gpio(GPIO_TypeDef *gpio, RCC_TypeDef *rcc);
    virtual ~Gpio() = default;

    Bit read(Pin gPin) override;
    virtual void write(Pin gPin, Bit value) override;
    void setMode(Pin gPin, Mode gMode) override;
    void setOutputType(Pin gPin, OutputType gOutputType) override;
    void setOutputSpeed(Pin gPin, OutputSpeed gOutputSpeed) override;
    void setPull(Pin gPin, Pull gPull) override;
    void  setAlternate(Pin gPin, Alt gAlt) override;
    void  toggle(Pin gPin) override;

  protected:
    inline virtual void  write(uint16_t value){
      gpio_->ODR = value;
    };
    inline virtual void  setMode(uint32_t value){
      gpio_->MODER = value;
    };
    inline virtual void  setOutputType(uint16_t value){
      gpio_->OTYPER = value;
    };
    inline virtual void  setOutputSpeed(uint32_t value){
      gpio_->OSPEEDR = value;
    };
    inline virtual void  setPull(uint32_t value){
      gpio_->PUPDR = value;
    };
    inline virtual void  setAlternateLow(uint32_t value){
      gpio_->AFR[0] = value;
    };
    inline virtual void  setAlternateHigh(uint32_t value){
      gpio_->AFR[1] = value;
    };
    inline virtual uint16_t read(){
      return static_cast<uint16_t>(gpio_->IDR);
    };
    inline virtual uint32_t getMode(){
      return gpio_->MODER;
    };
    inline virtual uint16_t getOutputType(){
      return static_cast<uint16_t>(gpio_->OTYPER & 0Xffff);
    };
    inline virtual uint32_t getOutputSpeed(){
      return gpio_->OSPEEDR;
    };
    inline virtual uint32_t getPull(){
      return gpio_->PUPDR;
    };
    inline virtual uint32_t getAlternateLow(){
      return gpio_->AFR[0];
    };
    inline virtual uint32_t getAlternateHigh(){
      return gpio_->AFR[1];
    };

  private:
    GPIO_TypeDef *gpio_;
};
}
