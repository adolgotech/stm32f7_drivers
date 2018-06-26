#pragma once
#include "gpio/gpio_defs.hpp"
namespace RCC{
  class Rcc{
  public:
      Rcc() = default;
      ~Rcc() = default;

      void softReset();
      void enableGpioClock(Port gPort);
      void setClockFreq(uint32_t freq);
      uint32_t clockFreq();
  };
}
