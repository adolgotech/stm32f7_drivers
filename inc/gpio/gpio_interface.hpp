#pragma once
#include <cstdint>
#include "gpio_defs.hpp"
#include "general/helpers.hpp"

namespace GPIO {
class GpioInterface {
  public:
    GpioInterface(){};
    virtual ~GpioInterface() = default;

    virtual Bit read(Pin gPin) = 0;
    virtual void  write(Pin gPin, Bit value) = 0;
    virtual void  setMode(Pin gPin, Mode gMode) = 0;
    virtual void  setOutputType(Pin gPin, OutputType gOutputType) = 0;
    virtual void  setOutputSpeed(Pin gPin, OutputSpeed gOutputSpeed) = 0;
    virtual void  setPull(Pin gPin, Pull gPull) = 0;
    virtual void  setAlternate(Pin gPin, Alt gAlt) = 0;
    virtual void  toggle(Pin gPin) = 0;
};
}
