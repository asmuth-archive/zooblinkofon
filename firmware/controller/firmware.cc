#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "vendor/light_ws2812.h"

void colorfade() {
  DDRC = 1; // pin 0 is output, everything else input

  const size_t kLedCount = 32;
  const double kFadeSpeed = 160;

  uint16_t j = 0;
  struct cRGB led[kLedCount];
  for (;; ++j) {
    for (size_t i = 0; i < kLedCount; ++i) {
      led[i].r = 170 + sin(j / kFadeSpeed) * 85;
      led[i].g = 0;
      led[i].b = 170 + sin(j / kFadeSpeed + M_PI) * 75;
    }

    ws2812_setleds(led, kLedCount);
    _delay_ms(1);
  }
}

void hauptsache_strobo() {
  DDRC = 1; // pin 0 is output, everything else input

  const size_t kLedCount = 32;
  const size_t kStroboSpeed = 10;

  uint16_t j = 0;
  struct cRGB led[kLedCount];
  for (;; ++j) {
    for (size_t i = 0; i < kLedCount; ++i) {
      if ((j / kStroboSpeed) % 2 == 0) {
        led[i].r = 255;
        led[i].g = 255;
        led[i].b = 255;
      } else {
        led[i].r = 0;
        led[i].g = 0;
        led[i].b = 0;
      }
    }

    ws2812_setleds(led, kLedCount);
    _delay_ms(1);
  }
}

int main(void) {
  colorfade();
}
