#pragma once
namespace GPIO {
enum class Port : uint8_t{
   A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7, I = 8, J = 9, K = 10,
   NUM_PORT = 11,
};

enum class Pin : uint8_t{
   _0 = 0, _1 = 1, _2 = 2, _3 = 3, _4 = 4, _5 = 5, _6 = 6, _7 = 7, _8 = 8,
   _9 = 9, _10 = 10, _11 = 11, _12 = 12, _13 = 13, _14 = 14, _15 = 15,
   NUM_PIN = 16,
};

enum class Mode : uint8_t {
  INPUT = 0,
  OUTPUT = 1,
  ALTERNATE = 2,
  ANALOG = 3,
  NUM_MODE = 4,
};

enum class OutputType : uint8_t {
  O_PP = 0,
  O_OD = 1,
  NUM_OTYPE = 2,
};

enum class OutputSpeed : uint8_t {
  LOW = 0,
  MEDIUM = 1,
  HIGH = 2,
  VERY_HIGH = 3,
  NUM_SPEED = 4,
};

enum class Pull : uint8_t {
  NO_PULL = 0,
  PULL_UP = 1,
  PULL_DOWN = 2,
  NUM_PULL = 3,
};

enum class Bit : uint8_t {
  CLR = 0,
  SET = 1,
  NUM_BIT = 2,
};

enum class Alt : uint8_t {
  AF0 = 0,
  AF1 = 1,
  AF2 = 2,
  AF3 = 3,
  AF4 = 4,
  AF5 = 5,
  AF6 = 6,
  AF7 = 7,
  AF8 = 8,
  AF9 = 9,
  AF10 = 10,
  AF11 = 11,
  AF12 = 12,
  AF13 = 13,
  AF14 = 14,
  AF15 = 15,
  NUM_AF = 16,
};

}
