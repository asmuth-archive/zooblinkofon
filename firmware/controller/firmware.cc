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
  protocol_reader.nextByte(data);

  switch (protocol_reader.getState()) {
    case ProtocolReader::S_LED_BEGIN:
      led_controller.beginLEDColors();
      break;
    case ProtocolReader::S_LED_DATA:
      led_controller.setNextLEDColor(uint8_t(data) << 1);
      break;
    case ProtocolReader::S_BUTTON_BEGIN:
      break;
  }
}

void magenta();
int main(void) {
  sei(); // enable interrupts

  led_controller.setLEDColors(0, 0, 0);
  serial_port.setReceiveCallback(&recv_data);
  led_controller.refreshDisplay();

  for (;;) {
    led_controller.refreshDisplay();
    _delay_ms(10);
  }
}

void magenta() {
  DDRC = 1; // pin 0 is output, everything else input

  const size_t kLedCount = 32;
  const double kFadeSpeed = 160;

  uint16_t j = 0;
  for (;; ++j) {
    for (size_t i = 0; i < kLedCount; ++i) {
      led_controller.setLEDColor(
          i,
          170 + sin(j / kFadeSpeed) * 85,
          0,
          170 + sin(j / kFadeSpeed + M_PI) * 75);
    }

    led_controller.refreshDisplay();

    //_delay_ms(1);
  }
}

void police() {
  DDRC = 1; // pin 0 is output, everything else input

  const size_t kLedCount = 32;
  const double kFadeSpeed = 10;

  uint16_t j = 0;
  for (;; ++j) {
    for (size_t i = 0; i < kLedCount; ++i) {
      led_controller.setLEDColor(
          i,
          128 + sin(j / kFadeSpeed) * 128,
          0,
          128 + sin(j / kFadeSpeed + M_PI / 2) * 128);
    }

    led_controller.refreshDisplay();

    _delay_ms(1);
  }
}
