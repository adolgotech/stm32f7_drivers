#define BOOST_TEST_MODULE Gpio Test
#include <boost/test/included/unit_test.hpp>
#include <array>
using std::array;
#include "mock_gpio.hpp"

using namespace GPIO;
struct GpioFixture{
  GpioFixture() : gpio(&hGpio, &hRcc){};
  GPIO_TypeDef hGpio = {};
  RCC_TypeDef hRcc = {};
  MockGpio gpio;
};

BOOST_AUTO_TEST_CASE(GpioTestClockConfig){
  // Ensure peripheral clock(s) is(are) enabled
  constexpr array<uint32_t, 11> gpioAddr{0x4002'0000, 0x4002'0400, 0x4002'0800,
                                         0x4002'0C00, 0x4002'1000, 0x4002'1400,
                                         0x4002'1800, 0x4002'1C00, 0x4002'2000,
                                         0x4002'2400, 0x4002'2800};
  uint8_t index = 0;
  for(auto addr : gpioAddr)
  {
    RCC_TypeDef rcc = {};
    MockGpio gpio(reinterpret_cast<GPIO_TypeDef*>(addr), &rcc);
    BOOST_TEST((rcc.AHB1ENR & 0x7FF) == (1 << index));
    index++;
  }
}

BOOST_FIXTURE_TEST_SUITE(GpioTestSuite, GpioFixture)

BOOST_AUTO_TEST_CASE(GpioTestModeInitConfiguration){
  BOOST_CHECK_EQUAL(gpio.getMode(), 0x0000'0000);
}

BOOST_AUTO_TEST_CASE(GpioTestSetMode){
  uint32_t testVal = 0x3214'5711;
  gpio.setMode(testVal);
  BOOST_CHECK_EQUAL(gpio.getMode(), testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetModeWithPin){
  BOOST_CHECK(gpio.getMode(Pin::_15) == Mode::INPUT);
  BOOST_CHECK(gpio.getMode(Pin::_3) == Mode::INPUT);
}

BOOST_AUTO_TEST_CASE(GpioTestSetModeWithPin){
  gpio.setMode(Pin::_7, Mode::OUTPUT);
  BOOST_CHECK(gpio.getMode(Pin::_7) == Mode::OUTPUT);
  BOOST_CHECK_EQUAL(gpio.getMode(), (static_cast<uint8_t>(Mode::OUTPUT) <<
                                    (static_cast<uint8_t>(Pin::_7) << 1)));
  gpio.setMode(Pin::_7, Mode::ALTERNATE);
  BOOST_CHECK(gpio.getMode(Pin::_7) == Mode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getMode(), (static_cast<uint8_t>(Mode::ALTERNATE)
                                    << (static_cast<uint8_t>(Pin::_7) << 1)));

  gpio.setMode(Pin::_9, Mode::OUTPUT);
  BOOST_CHECK(gpio.getMode(Pin::_9) == Mode::OUTPUT);
  //0100|1000|0000|0000|0000 -> 0x48000
  BOOST_CHECK_EQUAL(gpio.getMode(), (static_cast<uint8_t>(Mode::ALTERNATE)
                                    << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                    (static_cast<uint8_t>(Mode::OUTPUT) <<
                                    (static_cast<uint8_t>(Pin::_9) << 1)));
  gpio.setMode(Pin::_9, Mode::ALTERNATE);
  BOOST_CHECK(gpio.getMode(Pin::_9) == Mode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getMode(), (static_cast<uint8_t>(Mode::ALTERNATE)
                                    << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                    (static_cast<uint8_t>(Mode::ALTERNATE)
                                    << (static_cast<uint8_t>(Pin::_9) << 1)));
}

BOOST_AUTO_TEST_CASE(GpioTestOutputTypeInitConfiguration){
  BOOST_CHECK_EQUAL(gpio.getOutputType(), 0x0000);
}

BOOST_AUTO_TEST_CASE(GpioTestSetOutputType){
  uint32_t testVal = 0x5711;
  gpio.setOutputType(testVal);
  BOOST_CHECK_EQUAL(gpio.getOutputType(), testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetOutputTypeWithPin){
  BOOST_CHECK(gpio.getOutputType(Pin::_4) == OutputType::O_PP);
}

BOOST_AUTO_TEST_CASE(GpioTestSetOutputTypeWithPin){
  gpio.setOutputType(Pin::_4, OutputType::O_PP);
  BOOST_CHECK(gpio.getOutputType(Pin::_4) == OutputType::O_PP);
  gpio.setOutputType(Pin::_4, OutputType::O_OD);
  BOOST_CHECK(gpio.getOutputType(Pin::_4) == OutputType::O_OD);
}

BOOST_AUTO_TEST_CASE(GpioTestGetOutputSpeedInitConfiguration){
  // Test initial conditions
  BOOST_CHECK_EQUAL(gpio.getOutputSpeed(), 0x0000'0000);
}

BOOST_AUTO_TEST_CASE(GpioTestSetOutputSpeed){
  uint32_t testVal = 0x1457'8930;
  gpio.setOutputSpeed(testVal);
  BOOST_CHECK_EQUAL(gpio.getOutputSpeed(), testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetOutputSpeedTypeWithPin){
  BOOST_CHECK(gpio.getOutputSpeed(Pin::_9) == OutputSpeed::LOW);
}

BOOST_AUTO_TEST_CASE(GpioTestSetOutputSpeedTypeWithPin){
  OutputSpeed testVal = OutputSpeed::HIGH;
  gpio.setOutputSpeed(Pin::_0, testVal);
  BOOST_CHECK(gpio.getOutputSpeed(Pin::_0) == testVal);
  testVal = OutputSpeed::LOW;
  gpio.setOutputSpeed(Pin::_4, testVal);
  BOOST_CHECK(gpio.getOutputSpeed(Pin::_4) == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetPullInitConfiguration){
  // Test initial conditions
  BOOST_CHECK_EQUAL(gpio.getPull(), 0x0000'0000);
}

BOOST_AUTO_TEST_CASE(GpioTestSetPull){
  uint32_t testVal = 0x0000'0000;
  gpio.setPull(testVal);
  BOOST_CHECK_EQUAL(gpio.getPull(), testVal);
  testVal = 0x5157'30AF;
  gpio.setPull(testVal);
  BOOST_CHECK_EQUAL(gpio.getPull(), testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetPullWithPin){
  BOOST_CHECK(gpio.getPull(Pin::_0) == Pull::NO_PULL);
}

BOOST_AUTO_TEST_CASE(GpioTestSetPullWithPin){
  Pull testVal = Pull::NO_PULL;
  gpio.setPull(Pin::_0, testVal);
  BOOST_CHECK(gpio.getPull(Pin::_0) == testVal);

  testVal = Pull::PULL_UP;
  gpio.setPull(Pin::_0, testVal);
  BOOST_CHECK(gpio.getPull(Pin::_0) == testVal);

  testVal = Pull::PULL_DOWN;
  gpio.setPull(Pin::_13, testVal);
  BOOST_CHECK(gpio.getPull(Pin::_13) == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestReadInitConfiguration){
  // Test initial conditions
  BOOST_CHECK_EQUAL(gpio.read(), 0x0000'0000);
}

BOOST_AUTO_TEST_CASE(GpioTestWrite){
  uint32_t testVal = 0x0000;
  gpio.write(testVal);
  BOOST_CHECK_EQUAL(gpio.read(), testVal);
  testVal = 0x1287;
  gpio.write(testVal);
  BOOST_CHECK_EQUAL(gpio.read(), testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestReadWithPin){
  Bit testVal = Bit::CLR;
  BOOST_CHECK(gpio.read(Pin::_0) == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestWriteWithPin){
  Bit testVal = Bit::SET;
  gpio.write(Pin::_5, testVal);
  BOOST_CHECK(gpio.read(Pin::_5) == testVal);

  testVal = Bit::CLR;
  gpio.write(Pin::_5, testVal);
  BOOST_CHECK(gpio.read(Pin::_5) == testVal);

  testVal = Bit::SET;
  gpio.write(Pin::_11, testVal);
  BOOST_CHECK(gpio.read(Pin::_11) == testVal);

  testVal = Bit::CLR;
  gpio.write(Pin::_11, testVal);
  BOOST_CHECK(gpio.read(Pin::_11) == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetAlternateInitConfiguration){
  // Test initial conditions
  BOOST_CHECK(gpio.getAlternateLow() == 0x0000'0000);
  BOOST_CHECK(gpio.getAlternateHigh() == 0x0000'0000);
}

BOOST_AUTO_TEST_CASE(GpioTestSetAlternate){
  uint32_t testVal = 0x3214'AE30;
  gpio.setAlternateLow(testVal);
  BOOST_CHECK(gpio.getAlternateLow() == testVal);

  testVal = 0x1A40'32E3;
  gpio.setAlternateHigh(testVal);
  BOOST_CHECK(gpio.getAlternateHigh() == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestGetAlternateWithPin){
  BOOST_CHECK(gpio.getAlternate(Pin::_0) == Alt::AF0);
}

BOOST_AUTO_TEST_CASE(GpioTestSetAlternateWithPiin){
  Alt testVal = Alt::AF0;
  gpio.setAlternate(Pin::_0, testVal);
  BOOST_CHECK(gpio.getAlternate(Pin::_0) == testVal);

  testVal = Alt::AF9;
  gpio.setAlternate(Pin::_0, testVal);
  BOOST_CHECK(gpio.getAlternate(Pin::_0) == testVal);

  testVal = Alt::AF14;
  gpio.setAlternate(Pin::_8, testVal);
  BOOST_CHECK(gpio.getAlternate(Pin::_8) == testVal);
}

BOOST_AUTO_TEST_CASE(GpioTestToggle){
  Bit prevVal = gpio.read(Pin::_0);
  gpio.toggle(Pin::_0);
  Bit currVal = gpio.read(Pin::_0);
  BOOST_CHECK(currVal != prevVal);
  BOOST_CHECK(static_cast<Bit>(currVal) != static_cast<Bit>(prevVal));
  gpio.toggle(Pin::_0);
  Bit newVal = gpio.read(Pin::_0);
  BOOST_CHECK(static_cast<Bit>(newVal) == static_cast<Bit>(prevVal));
}

BOOST_AUTO_TEST_SUITE_END()
