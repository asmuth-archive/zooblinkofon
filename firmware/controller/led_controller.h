#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

struct __attribute__((packed)) Colour {
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

class LEDController {
public:

  static const uint16_t kLEDCount = 32;

  LEDController();

  void setAmbientColour(
      uint8_t red,
      uint8_t green,
      uint8_t blue);

  void setAmbientColour(const Colour& c);

  //void beginLEDColors();
  //void setNextLEDColor(uint8_t val);

  void refreshDisplay();

protected:
  Colour ambient_;
};

} // namespace avr
} // namespace iot9000

