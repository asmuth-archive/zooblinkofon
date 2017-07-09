#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "led_controller.h"
#include "protocol.h"

using namespace iot9000::avr;

SerialPort serial_port;
LEDController led_controller;
ProtocolReader protocol_reader;

ISR(USART_RX_vect) {
  serial_port.handleInterrupt();
}

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

  for (;;) {
    for (uint8_t n = 0; n < 5; n++) {
      led_controller.setButton(4 - n, 0);
      led_controller.setButton((4 - n) + 5, 0);
      led_controller.refreshDisplay();
      _delay_ms(200);
    }

    for (uint8_t n = 0; n < 5; n++) {
      led_controller.setButton(4 - n, 1);
      led_controller.setButton((4 - n) + 5, 1);
      led_controller.refreshDisplay();
      _delay_ms(200);
    }
  }
}

int main(void) {
  bootanim();

  return 0;
}

