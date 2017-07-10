#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"

namespace iot9000 {
namespace avr {

SerialPort::SerialPort() {
  UBRR0L = 0x19;
  UBRR0H = 0;
	UCSR0B = (1 << RXEN0);
	UCSR0C = (3 << UCSZ00);
}

uint8_t SerialPort::recvBlock() {
	for (;;) {
    uint8_t byte;
    if (recvNonblock(&byte)) {
      return byte;
    }
  }
}

bool SerialPort::recvNonblock(uint8_t* byte) {
  if (hasPendingData()) {
    *byte = UDR0;
    return true;
  } else {
    return false;
  }
}

bool SerialPort::hasPendingData() const {
  return UCSR0A & (1 << RXC0);
}

bool SerialPort::receivePacket(uint8_t* pkt) {
  uint8_t buf[SerialPort::kPacketLength];
  memset(buf, 0, sizeof(buf));

  for (uint8_t i = 0; ; ++i) {
    auto off = i % sizeof(buf);
    buf[off] = recvBlock();
 
    memcpy(pkt, buf + off, sizeof(buf) - off);
    memcpy(pkt + off, buf, off);

    if (verifyPacket(pkt)) {
      break;
    }
  }
}

bool SerialPort::verifyPacket(const uint8_t* pkt) {
  return pkt[6] == 0x42;
}

} // namespace avr
} // namespace iot9000
