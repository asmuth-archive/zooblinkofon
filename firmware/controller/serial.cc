#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"

namespace iot9000 {
namespace avr {

SerialPort::SerialPort() : receive_cb_(nullptr), recv_buf_len_(0) {
  // set hardware registers for serial console
  UBRR0L = (((F_CPU / (kClockBaud * 16UL))) - 1);
  UBRR0H = (((F_CPU / (kClockBaud * 16UL))) - 1) >> 8;
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
  char c = UDR0;

  cli();

  auto pos = recv_buf_len_;
  if (pos >= kRecvBufferSize) {
    goto exit;
  }

  recv_buf_[pos] = c;
  recv_buf_len_ = pos + 1;

  if (receive_cb_) {
    auto consumed = receive_cb_(recv_buf_, recv_buf_len_);
    if (consumed > 0) {
      if (consumed < recv_buf_len_) {
        memmove(recv_buf_, recv_buf_ + consumed, recv_buf_len_ - consumed);
      }

      recv_buf_len_ -= consumed;
    }
  }

exit:

  sei();
}

void SerialPort::setReceiveCallback(ReceiveCallbackType cb) {
  receive_cb_ = cb;
}

} // namespace avr
} // namespace iot9000


