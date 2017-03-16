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

ISR(TIMER0_OVF_vect) {
  led_controller.refreshDisplay();
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
  }
}

int main(void) {
  sei(); // enable interrupts

  // enable timer interrupt
  TIMSK0 = (1 << TOIE0);
  TCNT0 = 0x00;
  TCCR0B |= (1 << CS02) | (1 << CS00);

  serial_port.setReceiveCallback(&recv_data);

  for (;;) {}
}

//void colorfade() {
//  DDRC = 1; // pin 0 is output, everything else input
//
//  const size_t kLedCount = 32;
//  const double kFadeSpeed = 160;
//
//  uint16_t j = 0;
//  struct cRGB led[kLedCount];
//  for (;; ++j) {
//    for (size_t i = 0; i < kLedCount; ++i) {
//      led[i].r = 170 + sin(j / kFadeSpeed) * 85;
//      led[i].g = 0;
//      led[i].b = 170 + sin(j / kFadeSpeed + M_PI) * 75;
//    }
//
//    ws2812_setleds(led, kLedCount);
//    _delay_ms(1);
//  }
//}
