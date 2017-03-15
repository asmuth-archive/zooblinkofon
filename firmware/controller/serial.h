#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class SerialPort {
public:

  static const uint32_t kClockBaud = 38400;

  static SerialPort* getPort();

  uint32_t sendNonblock(const char* data, uint32_t len);

protected:

  SerialPort();

};


} // namespace avr
} // namespace iot9000

