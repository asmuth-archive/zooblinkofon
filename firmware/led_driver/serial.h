#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  SerialPort();

  bool recvPacket(uint8_t* pkt, uint16_t len);
  bool recv(uint8_t* byte);
  bool recvNonblock(uint8_t* byte);
  bool hasPendingData() const;
  void wait(uint32_t t) const;

};

} // namespace avr
} // namespace iot9000
