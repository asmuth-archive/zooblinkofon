#include "led_controller.h"
#include "vendor/light_ws2812.h"

namespace iot9000 {
namespace avr {

LEDController::LEDController() : cur_(0) {
  for (uint16_t i = 0; i < kLEDCount; ++i) {
    led_state_[i].r = 0;
    led_state_[i].g = 0;
    led_state_[i].b = 0;
  }
}

void LEDController::setLEDColors(
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  for (uint16_t i = 0; i < kLEDCount; ++i) {
    led_state_[i].r = red;
    led_state_[i].g = green;
    led_state_[i].b = blue;
  }
}

void LEDController::setLEDColor(
    uint16_t led_idx,
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  led_state_[led_idx].r = red;
  led_state_[led_idx].g = green;
  led_state_[led_idx].b = blue;
}

void LEDController::beginLEDColors() {
  cur_ = 0;
}

void LEDController::setNextLEDColor(uint8_t val) {
  switch (cur_ % 3) {
    case 0:
      led_state_[cur_ / 3].r = val;
      break;
    case 1:
      led_state_[cur_ / 3].g = val;
      break;
    case 2:
      led_state_[cur_ / 3].b = val;
      break;
  }

  cur_ = (cur_ + 1) % (kLEDCount * 3);
}

void LEDController::refreshDisplay() {
  ws2812_setleds(led_state_, kLEDCount);
}

} // namespace avr
} // namespace iot9000

