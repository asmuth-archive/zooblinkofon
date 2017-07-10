#include "driver.h"
#include "vendor/light_ws2812.h"

namespace iot9000 {
namespace avr {

const uint8_t LEDController::kButtonMap[] = {
  6,
  4,
  2,
  5,
  3,
  12,
  10,
  11,
  14,
  13
};

LEDController::LEDController() : buttons_(0) {
  ambient_.r = 0;
  ambient_.g = 0;
  ambient_.b = 0;

  DDRD |= 1 << kButtonDataPin;
  DDRD |= 1 << kButtonClockPin;
  DDRD |= 1 << kButtonLatchPin;
}

void LEDController::setButtons(ButtonRegisterType r) {
  buttons_ = r;
}

void LEDController::setButton(uint8_t index, bool state) {
  if (state) {
    buttons_ |= 1 << kButtonMap[index];
  } else {
    buttons_ &= ~(1 << kButtonMap[index]);
  }
}

void LEDController::setAmbientColour(const Colour& c) {
  ambient_ = c;
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

static void setp(int p, int s) {
  if (s) {
    PORTD |= (1 << p);
  } else {
    PORTD &= ~(1 << p);
  }
}

void LEDController::refreshDisplay() {
  // write ws2812 data
  cli();
  ws2812_setleds(&ambient_, 32);
  sei();

  // write buttons to shift register
  setp(kButtonLatchPin, 0);

  for (uint8_t i = 0; i < kButtonCount; ++i) {
    setp(kButtonClockPin, 0);
    setp(kButtonDataPin, buttons_ & (1 << i));
    _delay_us(10);
    setp(kButtonClockPin, 1);
    _delay_us(10);
  }

  setp(kButtonLatchPin, 1);
}

} // namespace avr
} // namespace iot9000

