#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  using ReceiveCallbackType = uint16_t (*)(const char* data, uint16_t len);

  static const uint32_t kClockBaud = 38400;
  static const uint16_t kRecvBufferSize = 512;

  SerialPort();

  uint16_t sendNonblock(const char* data, uint16_t len);

  void setReceiveCallback(ReceiveCallbackType receive_cb);
  void handleInterrupt();

protected:
  ReceiveCallbackType receive_cb_;
  char recv_buf_[kRecvBufferSize];
  uint16_t recv_buf_len_;
};

} // namespace avr
} // namespace iot9000

