#pragma once
#include <stdint.h>

namespace iot9000 {
namespace avr {

class ProtocolReader {
public:

  enum ProtocolReaderState {
    S_IDLE,
    S_LED_BEGIN,
    S_LED_DATA,
    S_BUTTON_BEGIN,
    S_BUTTON_DATA
  };

  ProtocolReader();

  void nextByte(uint8_t c);
  ProtocolReaderState getState() const;

protected:
  ProtocolReaderState state_;
};

} // namespace avr
} // namespace iot9000

