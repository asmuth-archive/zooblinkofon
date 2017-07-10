#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "serial.h"
#include "driver.h"

using namespace iot9000::avr;

static const uint8_t kPacketLength = 5;

SerialPort serial_port;
LEDController led_controller;

void bootanim() {
  led_controller.setAmbientColour(0, 0, 0);
  led_controller.setButtons(0);
  led_controller.refreshDisplay();

  for (uint8_t n = 0; n < 5; n++) {
    led_controller.setButton(4 - n, 1);
    led_controller.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = (n * 50) + i;
      led_controller.setAmbientColour(b, b, b);
      led_controller.refreshDisplay();
      _delay_ms(5);
    }
  }

  for (uint8_t n = 0; n < 5; n++) {
    led_controller.setButton(4 - n, 1);
    led_controller.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = 250 - ((n * 50) + i);
      led_controller.setAmbientColour(b, b, b);
      led_controller.refreshDisplay();
      _delay_ms(5);
    }
  }

  led_controller.setAmbientColour(0, 0, 0);
  led_controller.refreshDisplay();
}

void idleanim() {
  led_controller.setAmbientColour(0, 0, 0);
  led_controller.setButtons(0);
  led_controller.refreshDisplay();

  while (!serial_port.hasPendingData()) {
    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_controller.setButton(4 - n, 0);
      led_controller.setButton((4 - n) + 5, 0);
      led_controller.refreshDisplay();
      serial_port.wait(200);
    }

    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_controller.setButton(4 - n, 1);
      led_controller.setButton((4 - n) + 5, 1);
      led_controller.refreshDisplay();
      serial_port.wait(200);
    }
  }
}

void update(uint8_t* pkt) {
  led_controller.setAmbientColour(pkt[0], pkt[1], pkt[2]);
  led_controller.setButtons(uint16_t(pkt[3]) | (uint16_t(pkt[4]) << 8));
  led_controller.refreshDisplay();
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

