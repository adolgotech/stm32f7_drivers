#pragma once
#include "gpio_interface.hpp"
#include <cstdint>

enum class Port : uint8_t{
   A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7, I = 8, J = 9, K = 10
};

enum class Pin : uint8_t{
   _0 = 0, _1 = 1, _2 = 2, _3 = 3, _4 = 4, _5 = 5, _6 = 6, _7 = 7, _8 = 8,
   _9 = 9, _10 = 10, _11 = 11, _12 = 12, _13 = 13, _14 = 14, _15 = 15
};

enum class GpioMode : uint8_t {
  INPUT = 0,
  GENERAL = 1,
  ALTERNATE = 2,
  ANALOG = 3
};

class MockGpio : public GpioInterface {
  public:
    MockGpio();
    ~MockGpio();

    uint32_t getPortMode(Port gPort);
    GpioMode getPinMode(Port gPort, Pin gPin);
    uint16_t getPortOutputType(Port gPort);
    void setPortMode(Port gPort, uint32_t value);
    void setPinMode(Port gPort, Pin gPin, GpioMode gMode);
    void setPortOutputType(Port gPort, uint16_t value);

  private:
    uint32_t portMode_[11];
    uint32_t portOType_[11];
};
