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

int main(void) {
  sei(); // enable interrupts

  led_controller.setLEDColors(0, 0, 0);
  serial_port.setReceiveCallback(&recv_data);
  led_controller.refreshDisplay();

  for (;;) {
    led_controller.refreshDisplay();
    _delay_ms(16);
  }
}

