#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "serial.h"
#include "driver.h"

using namespace iot9000::avr;

SerialPort serial_port;
LEDController led_controller;

void bootanim() {
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
  while (!serial_port.hasPendingData()) {
    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_controller.setButton(4 - n, 0);
      led_controller.setButton((4 - n) + 5, 0);
      led_controller.refreshDisplay();
      _delay_ms(200);
    }

    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_controller.setButton(4 - n, 1);
      led_controller.setButton((4 - n) + 5, 1);
      led_controller.refreshDisplay();
      _delay_ms(200);
    }
  }
}

int main(void) {
  bootanim();
  idleanim();

  uint8_t pkt[SerialPort::kPacketLength];
  serial_port.receivePacket(pkt);
  
  led_controller.setAmbientColour(255, 0, 0);
  led_controller.refreshDisplay();

  return 0;
}

