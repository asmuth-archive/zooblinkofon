#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "led_controller.h"

iot9000::avr::SerialPort serial_port;
iot9000::avr::LEDController led_controller;

ISR(USART_RX_vect) {
  serial_port.handleInterrupt();
}

ISR(TIMER0_OVF_vect) {
  led_controller.refreshDisplay();
}

uint16_t execute_command(const char* data, uint16_t len) {
  switch (data[0]) {
    case 'q':
      led_controller.setLEDColors(0, 0, 0);
      break;
    case 'a':
      led_controller.setLEDColors(255, 0, 0);
      break;
    case 's':
      led_controller.setLEDColors(0, 255, 0);
      break;
    case 'd':
      led_controller.setLEDColors(0, 0, 255);
      break;
    case 'w':
      led_controller.setLEDColors(255, 255, 255);
      break;
    default:
      led_controller.setLEDColors(255, 0, 255);
      break;
  }

  return 1;
}

int main(void) {
  sei(); // enable interrupts

  // enable timer interrupt
  TIMSK0 = (1 << TOIE0);
  TCNT0 = 0x00;
  TCCR0B |= (1 << CS02) | (1 << CS00);

  led_controller.refreshDisplay();
  serial_port.setReceiveCallback(&execute_command);

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
//
//void hauptsache_strobo() {
//  DDRC = 1; // pin 0 is output, everything else input
//
//  const size_t kLedCount = 32;
//  const size_t kStroboSpeed = 10;
//
//  uint32_t j = 0;
//  struct cRGB led[kLedCount];
//  for (;j < kStroboSpeed * 10; ++j) {
//    for (size_t i = 0; i < kLedCount; ++i) {
//      if ((j / kStroboSpeed) % 2 == 0) {
//        led[i].r = 255;
//        led[i].g = 0;
//        led[i].b = 255;
//      } else {
//        led[i].r = 0;
//        led[i].g = 0;
//        led[i].b = 0;
//      }
//    }
//
//    ws2812_setleds(led, kLedCount);
//    _delay_ms(1);
//  }
//}
