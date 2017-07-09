#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"

namespace iot9000 {
namespace avr {

SerialPort::SerialPort() : rxcb_(nullptr), txbuf_len_(0) {
  // set hardware registers for 19200 baud
  UBRR0L = 0x03;
  UBRR0H = 0;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
}

uint16_t SerialPort::sendNonblock(const char* data, uint16_t len) {
  uint16_t bytes_sent = 0;

  while (bytes_sent < len && (UCSR0A & (1 << UDRE0))) {
    UDR0 = *data++;
    ++bytes_sent;
  }

  return bytes_sent;
}

void SerialPort::handleInterrupt() {
  if (UCSR0A & (1 << RXC0)) {
    char c = UDR0;

    if (rxcb_) {
      rxcb_(c);
    }
  }
}

void SerialPort::setReceiveCallback(ReceiveCallbackType cb) {
  rxcb_ = cb;
}

} // namespace avr
} // namespace iot9000


