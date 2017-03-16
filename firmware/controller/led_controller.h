#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

struct __attribute__((packed)) LEDState {
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

class LEDController {
public:

  static const uint16_t kLEDCount = 64;

  LEDController();

  void setLEDColors(
      uint8_t red,
      uint8_t green,
      uint8_t blue);

  void setLEDColor(
      uint16_t led_idx,
      uint8_t red,
      uint8_t green,
      uint8_t blue);

  void beginLEDColors();
  void setNextLEDColor(uint8_t val);

  void refreshDisplay();

protected:
  LEDState led_state_[kLEDCount];
  uint16_t cur_;
};

} // namespace avr
} // namespace iot9000

