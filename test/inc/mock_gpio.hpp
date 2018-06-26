#pragma once
#include <cstdint>
#include "gpio.hpp"

namespace GPIO {
class MockGpio : public Gpio {
  public:
    MockGpio(GPIO_TypeDef *gpio, RCC_TypeDef *rcc);
    MockGpio();
    ~MockGpio();

    using Gpio::setMode;
    using Gpio::setOutputType;
    using Gpio::setOutputSpeed;
    using Gpio::setPull;
    using Gpio::read;
    using Gpio::setAlternate;
    using Gpio::toggle;

    void write(Pin gPin, Bit value) override;

    // These are private in the implementation
    // Port access functions
    uint32_t getMode() override;
    uint16_t getOutputType() override;
    uint32_t getOutputSpeed() override;
    uint32_t getPull() override;
    uint32_t getAlternateLow() override;
    uint32_t getAlternateHigh() override;
    uint16_t read() override;

    void write(uint16_t) override;
    void setMode(uint32_t value) override;
    void setOutputType(uint16_t value) override;
    void setOutputSpeed(uint32_t value) override;
    void setPull(uint32_t value) override;
    void setAlternateLow(uint32_t value) override;
    void setAlternateHigh(uint32_t value) override;

    // Pin access functions
    Mode getMode(Pin gPin);
    OutputType getOutputType(Pin gPin);
    OutputSpeed getOutputSpeed(Pin gPin);
    Pull getPull(Pin gPin);
    Alt getAlternate(Pin gPin);

  private:
    void bitSetClear(uint32_t value);
    GPIO_TypeDef *gpio_;
};
}
