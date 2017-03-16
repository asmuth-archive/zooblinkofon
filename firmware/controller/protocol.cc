#include "protocol.h"

namespace iot9000 {
namespace avr {

ProtocolReader::ProtocolReader() : state_(S_IDLE) {}

void ProtocolReader::nextByte(uint8_t c) {
  switch (c) {
    case 0x80:
      state_ = S_LED_BEGIN;
      return;
    case 0x81:
      state_ = S_BUTTON_BEGIN;
      return;
    default:
      break;
  }

  switch (state_) {
    case S_IDLE:
      state_ = S_IDLE;
      break;
    case S_LED_BEGIN:
    case S_LED_DATA:
      state_ = S_LED_DATA;
      break;
    case S_BUTTON_BEGIN:
    case S_BUTTON_DATA:
      state_ = S_BUTTON_DATA;
      break;
  }
}

ProtocolReader::ProtocolReaderState ProtocolReader::getState() const {
  return state_;
}

} // namespace avr
} // namespace iot9000

