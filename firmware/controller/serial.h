#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  using ReceiveCallbackType = void (*)(char data);

  static const uint32_t kClockBaud = 38400 * 8;
  static const uint16_t kTransmitBufferSize = 32;

  SerialPort();

  uint16_t sendNonblock(const char* data, uint16_t len);

  void setReceiveCallback(ReceiveCallbackType rxcb);
  void handleInterrupt();

protected:
  ReceiveCallbackType rxcb_;
  char txbuf_[kTransmitBufferSize];
  uint16_t txbuf_len_;
};

} // namespace avr
} // namespace iot9000

