#include "serial.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


extern void hauptsache_strobo();

namespace iot9000 {
namespace avr {

static SerialPort hw_uart0;

SerialPort::SerialPort() : receive_cb_(nullptr) {
  // set hardware registers for serial console
  UBRR0L = (((F_CPU / (kClockBaud * 16UL))) - 1);
  UBRR0H = (((F_CPU / (kClockBaud * 16UL))) - 1) >> 8;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
}

SerialPort* SerialPort::getPort() {
  return &hw_uart0;
}

uint32_t SerialPort::sendNonblock(const char* data, uint32_t len) {
  uint32_t bytes_sent = 0;

  while (bytes_sent < len && (UCSR0A & (1 << UDRE0))) {
    UDR0 = *data++;
    ++bytes_sent;
  }

  return bytes_sent;
}

void SerialPort::handleInterrupt() {
  char c = UDR0;
  if (receive_cb_) {
    receive_cb_();
  }
}

void SerialPort::setReceiveCallback(ReceiveCallbackType cb) {
  receive_cb_ = cb;
}

} // namespace avr
} // namespace iot9000


ISR(USART_RX_vect) {
  iot9000::avr::hw_uart0.handleInterrupt();
}

