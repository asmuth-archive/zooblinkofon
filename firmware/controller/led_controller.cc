#include "led_controller.h"
#include "vendor/light_ws2812.h"

namespace iot9000 {

LEDController::LEDController() {
  for (uint16_t i = 0; i < kLEDCount; ++i) {
    led_state[i].r = 255;
    led_state[i].g = 255;
    led_state[i].b = 255;
  }
}

void LEDController::refreshDisplay() {
  ws2812_setleds(led_state, kLEDCount);
}

} // namespace iot9000

