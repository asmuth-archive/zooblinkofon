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

  using ButtonRegisterType = uint16_t;
  static const uint8_t kButtonCount = sizeof(ButtonRegisterType) * 8;
  static const uint8_t kButtonDataPin = 2;
  static const uint8_t kButtonClockPin = 3;
  static const uint8_t kButtonLatchPin = 4;
  static const uint8_t kButtonMap[kButtonCount];

  LEDController();

  void setButtons(ButtonRegisterType r);
  void setButton(uint8_t index, bool state);

  void setAmbientColour(const Colour& c);
  void setAmbientColour(
      uint8_t red,
      uint8_t green,
      uint8_t blue);

  void refreshDisplay();

protected:
  Colour ambient_;
  ButtonRegisterType buttons_;
};

} // namespace avr
} // namespace iot9000

