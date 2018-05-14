#pragma once
#include "gpio_interface.hpp"

class Gpio : public GpioInterface {
  public:
    Gpio();
    virtual ~Gpio();
};
