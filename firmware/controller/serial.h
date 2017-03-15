#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  using ReceiveCallbackType = void (*)();

  static const uint32_t kClockBaud = 38400;

  SerialPort();

  uint32_t sendNonblock(const char* data, uint32_t len);

  void setReceiveCallback(ReceiveCallbackType receive_cb);
  void handleInterrupt();

protected:
  ReceiveCallbackType receive_cb_;
};

} // namespace avr
} // namespace iot9000

