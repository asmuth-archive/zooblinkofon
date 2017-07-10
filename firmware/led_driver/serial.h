#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  static const uint8_t kPacketLength = 7;

  SerialPort();

  uint8_t recvBlock();
  bool recvNonblock(uint8_t* byte);
  bool hasPendingData() const;

  bool receivePacket(uint8_t* pkt);
  bool verifyPacket(const uint8_t* pkt);

};

} // namespace avr
} // namespace iot9000
