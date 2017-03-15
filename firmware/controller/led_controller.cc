#include "led_controller.h"
#include "vendor/light_ws2812.h"

namespace iot9000 {
namespace avr {

LEDController::LEDController() {
  for (uint16_t i = 0; i < kLEDCount; ++i) {
    led_state[i].r = 0;
    led_state[i].g = 0;
    led_state[i].b = 0;
  }
}

void LEDController::setLEDColor(
    uint16_t led_idx,
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  led_state[led_idx].r = red;
  led_state[led_idx].g = green;
  led_state[led_idx].b = blue;
}

void LEDController::refreshDisplay() {
  cli(); // disable interrupts
  ws2812_setleds(led_state, kLEDCount);
  sei(); // enable interrupts
}

} // namespace avr
} // namespace iot9000

