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
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::A, Pin::_15), 0x2);
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::B, Pin::_3), 0x2);
}

BOOST_AUTO_TEST_CASE(GpioTestSetPinMode){
  MockGpio gpio;
  gpio.setPortMode(Port::A, 0x00000000);
  gpio.setPinMode(Port::A, Pin::_7, 0x01);
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::A, Pin::_7), 1);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (1 << (static_cast<uint8_t>(Pin::_7) << 1)));
  gpio.setPinMode(Port::A, Pin::_7, 2);
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::A, Pin::_7), 2);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (2 << (static_cast<uint8_t>(Pin::_7) << 1)));

  gpio.setPinMode(Port::A, Pin::_9, 1);
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::A, Pin::_9), 1);
  //0100|1000|0000|0000|0000 -> 0x48000
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), /*0x48000*/(2 << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                               (1 << (static_cast<uint8_t>(Pin::_9) << 1)));
  gpio.setPinMode(Port::A, Pin::_9, 2);
  BOOST_CHECK_EQUAL(gpio.getPinMode(Port::A, Pin::_9), 2);
  BOOST_CHECK_EQUAL(gpio.getPortMode(Port::A), (2 << (static_cast<uint8_t>(Pin::_7) << 1)) |
                                               (2 << (static_cast<uint8_t>(Pin::_9) << 1)));
}

// BOOST_AUTO_TEST_CASE(GpioTestConfigAnalog){
//   BOOST_CHECK_EQUAL(gpio.MODER, 0X);
// }
