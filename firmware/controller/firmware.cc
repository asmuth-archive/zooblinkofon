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

void recv_data(char data) {
}

#define PDATA 2
#define PCLCK 3
#define PLTCH 4

void setp(int p, int s) {
  if (s) {
    PORTD |= (1 << p);
  } else {
    PORTD &= ~(1 << p);
  }
}

void blink() {
  for (int i = 0; i < 16; ++i) {
    setp(PLTCH, 0);

    for (size_t n = 0; n < 16; ++n) {
      setp(PCLCK, 0);
      setp(PDATA, i % 16 == n);
      _delay_ms(10);
      setp(PCLCK, 1);
      led_controller.refreshDisplay();
    }

    setp(PLTCH, 1);
  }
}

int main(void) {
  DDRD |= 1 << PDATA;
  DDRD |= 1 << PCLCK;
  DDRD |= 1 << PLTCH;

  for (;;) {
    led_controller.setAmbientColour(255, 0, 0);
    led_controller.refreshDisplay();
    blink();
    led_controller.setAmbientColour(0, 0, 0);
    led_controller.refreshDisplay();
    _delay_ms(100);
  }

  return 0;
}

