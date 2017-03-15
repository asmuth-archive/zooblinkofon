#include "serial.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

namespace iot9000 {
namespace avr {

static SerialPort* hw_uart0;

SerialPort* SerialPort::getPort() {
  if (!hw_uart0) {
    // set hardware registers for serial console
    UBRR0L = (((F_CPU / (kClockBaud * 16UL))) - 1);
    UBRR0H = (((F_CPU / (kClockBaud * 16UL))) - 1) >> 8;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  }

  return hw_uart0;
}

uint32_t SerialPort::sendNonblock(const char* data, uint32_t len) {
  uint32_t bytes_sent = 0;

  while (bytes_sent < len && (UCSR0A & (1 << UDRE0))) {
    UDR0 = *data++;
    ++bytes_sent;
  }

  return bytes_sent;
}

} // namespace avr
} // namespace iot9000

