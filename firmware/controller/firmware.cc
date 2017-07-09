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

int main(void) {
  for (uint32_t n = 0; ; n++) {
    for (uint32_t i = 0; i < 16; i++) {
      led_controller.setButton(i, i == (n % 10));
    }

    auto b = (n % 2) * 30;
    led_controller.setAmbientColour(b, b, b);
    led_controller.refreshDisplay();
    _delay_ms(200);
  }

  return 0;
}

