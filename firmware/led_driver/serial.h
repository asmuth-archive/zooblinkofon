#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  static const uint8_t kPacketLength = 8;

  SerialPort();

  bool recvBlock(uint8_t* byte, uint32_t timeout = 500);
  bool recvNonblock(uint8_t* byte);
  bool hasPendingData() const;

  bool receivePacket(uint8_t* pkt);
  bool verifyPacket(const uint8_t* pkt);

  void wait(uint32_t t) const;

};

} // namespace avr
} // namespace iot9000
