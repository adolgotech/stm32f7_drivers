#define BOOST_TEST_MODULE Gpio Test
#include <boost/test/included/unit_test.hpp>
#include <initializer_list>
#include "mock_gpio.hpp"

BOOST_AUTO_TEST_CASE(GpioTestModeInitConfiguration){
  MockGpio gpio;
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), 0XA8000000);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::B), 0X00000280);
  for(auto port : {Port::C, Port::D, Port::E, Port::F, Port::G, Port::H,
                   Port::I, Port::J, Port::K}){
    BOOST_CHECK_EQUAL(gpio.getPortMode(port), 0X00000000);
  }
}

BOOST_AUTO_TEST_CASE(GpioTestGetPinMode){
  MockGpio gpio;
  BOOST_CHECK(gpio.getPinMode(Port::A, Pin::_15) == GpioMode::ALTERNATE);
  BOOST_CHECK(gpio.getPinMode(Port::B, Pin::_3) == GpioMode::ALTERNATE);
}

BOOST_AUTO_TEST_CASE(GpioTestSetPinMode){
  MockGpio gpio;
  gpio.setPortMode(Port::A, 0x00000000);
  gpio.setPinMode(Port::A, Pin::_7, GpioMode::GENERAL);
  BOOST_CHECK(gpio.getPinMode(Port::A, Pin::_7) == GpioMode::GENERAL);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (1 << (static_cast<uint8_t>(Pin::_7) << 1)));
  gpio.setPinMode(Port::A, Pin::_7, GpioMode::ALTERNATE);
  BOOST_CHECK(gpio.getPinMode(Port::A, Pin::_7) == GpioMode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (2 << (static_cast<uint8_t>(Pin::_7) << 1)));

  gpio.setPinMode(Port::A, Pin::_9, GpioMode::GENERAL);
  BOOST_CHECK(gpio.getPinMode(Port::A, Pin::_9) == GpioMode::GENERAL);
  //0100|1000|0000|0000|0000 -> 0x48000
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (2 << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                               (1 << (static_cast<uint8_t>(Pin::_9) << 1)));
  gpio.setPinMode(Port::A, Pin::_9, GpioMode::ALTERNATE);
  BOOST_CHECK(gpio.getPinMode(Port::A, Pin::_9) == GpioMode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (2 << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                               (2 << (static_cast<uint8_t>(Pin::_9) << 1)));

  gpio.setPortMode(Port::B, 0x00000000);
  gpio.setPinMode(Port::B, Pin::_4, GpioMode::GENERAL);
  BOOST_CHECK(gpio.getPinMode(Port::B, Pin::_4) == GpioMode::GENERAL);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::B), (1 << (static_cast<uint8_t>(Pin::_4) << 1)));
  gpio.setPinMode(Port::B, Pin::_4, GpioMode::ALTERNATE);
  BOOST_CHECK(gpio.getPinMode(Port::B, Pin::_4) == GpioMode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::B), (2 << (static_cast<uint8_t>(Pin::_4) << 1)));

  gpio.setPinMode(Port::B, Pin::_11, GpioMode::GENERAL);
  BOOST_CHECK(gpio.getPinMode(Port::B, Pin::_11) == GpioMode::GENERAL);
  //0100|1000|0000|0000|0000 -> 0x48000
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::B), (2 << (static_cast<uint8_t>(Pin::_4) << 1)) |
                                              (1 << (static_cast<uint8_t>(Pin::_11) << 1)));
  gpio.setPinMode(Port::B, Pin::_11, GpioMode::ALTERNATE);
  BOOST_CHECK(gpio.getPinMode(Port::B, Pin::_11) == GpioMode::ALTERNATE);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::B), (2 << (static_cast<uint8_t>(Pin::_4) << 1)) |
                                              (2 << (static_cast<uint8_t>(Pin::_11) << 1)));
}

BOOST_AUTO_TEST_CASE(GpioTestPortOutputType){
  MockGpio gpio;
  // Test initial conditions
  for(auto port : {Port::A, Port::B, Port::C, Port::D, Port::E, Port::F,
                   Port::G, Port::H, Port::I, Port::J, Port::K}){
    BOOST_CHECK_EQUAL(gpio.getPortOutputType(port), 0x0000);
  }
  // General test, set and retrieve
  gpio.setPortOutputType(Port::C, 0x1234);
  BOOST_CHECK_EQUAL(gpio.getPortOutputType(Port::C), 0X1234);

  // Check the boundary, should not be able to take numbers greater than 65535
  gpio.setPortOutputType(Port::A, 0);
  BOOST_CHECK(gpio.getPortOutputType(Port::A) == 0);

}
