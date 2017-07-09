#include "led_controller.h"
#include "vendor/light_ws2812.h"

namespace iot9000 {
namespace avr {

LEDController::LEDController()  {
  ambient_.r = 0;
  ambient_.g = 0;
  ambient_.b = 0;
}

void LEDController::setAmbientColour(
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  Colour c;
  c.r = red;
  c.g = green;
  c.b = blue;

  setAmbientColour(c);
}

void LEDController::setAmbientColour(const Colour& c) {
  ambient_ = c;
}

void LEDController::refreshDisplay() {
  cli();
  ws2812_setleds(&ambient_, 32);
  sei();
}

} // namespace avr
} // namespace iot9000

