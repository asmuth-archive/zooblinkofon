#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "serial.h"
#include "driver.h"

using namespace iot9000::avr;

static const uint8_t kPacketLength = 5;

SerialPort serial_port;
LEDDriver led_driver;

void bootanim() {
  led_driver.clear();

  for (uint8_t n = 0; n < 5; n++) {
    led_driver.setButton(4 - n, 1);
    led_driver.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = (n * 50) + i;
      led_driver.setAmbientColour(b, b, b);
      led_driver.refreshDisplay();
      _delay_ms(5);
    }
  }

  for (uint8_t n = 0; n < 5; n++) {
    led_driver.setButton(4 - n, 1);
    led_driver.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = 250 - ((n * 50) + i);
      led_driver.setAmbientColour(b, b, b);
      led_driver.refreshDisplay();
      _delay_ms(5);
    }
  }

  led_driver.setAmbientColour(0, 0, 0);
  led_driver.refreshDisplay();
}

void idleanim() {
  led_driver.clear();

  while (!serial_port.hasPendingData()) {
    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_driver.setButton(4 - n, 0);
      led_driver.setButton((4 - n) + 5, 0);
      led_driver.refreshDisplay();
      serial_port.wait(200);
    }

    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_driver.setButton(4 - n, 1);
      led_driver.setButton((4 - n) + 5, 1);
      led_driver.refreshDisplay();
      serial_port.wait(200);
    }
  }
}

void update(uint8_t* pkt) {
  auto buttons = uint16_t(pkt[3]) | (uint16_t(pkt[4]) << 8);
  led_driver.setButton(0, buttons & (1 << 0));
  led_driver.setButton(1, buttons & (1 << 1));
  led_driver.setButton(2, buttons & (1 << 2));
  led_driver.setButton(3, buttons & (1 << 3));
  led_driver.setButton(4, buttons & (1 << 4));
  led_driver.setButton(5, buttons & (1 << 5));
  led_driver.setButton(6, buttons & (1 << 6));
  led_driver.setButton(7, buttons & (1 << 7));
  led_driver.setButton(8, buttons & (1 << 8));
  led_driver.setButton(9, buttons & (1 << 9));
  led_driver.setAmbientColour(pkt[0], pkt[1], pkt[2]);
  led_driver.refreshDisplay();
}

int main(void) {
  bootanim();

  for (;;) {
    idleanim();

    for (uint32_t timeout = 0; timeout < (F_CPU / 8192); ++timeout) {
      uint8_t pkt[kPacketLength];
      if (serial_port.recvPacket(pkt, sizeof(pkt))) {
        update(pkt);
        timeout = 0;
      }
    }
  }

  return 0;
}

