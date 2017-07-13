#pragma once
#include <stdint.h>

namespace zooblinkofon {
namespace led_driver {

struct __attribute__((packed)) Colour {
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

class LEDDriver {
public:

  using ButtonRegisterType = uint16_t;
  static const uint8_t kButtonCount = sizeof(ButtonRegisterType) * 8;
  static const uint8_t kButtonDataPin = 2;
  static const uint8_t kButtonClockPin = 3;
  static const uint8_t kButtonLatchPin = 4;
  static const uint8_t kButtonMap[kButtonCount];

  LEDDriver();

  void setButton(uint8_t index, bool state);

  void setAmbientColour(const Colour& c);
  void setAmbientColour(
      uint8_t red,
      uint8_t green,
      uint8_t blue);

  void refreshDisplay();
  void clear();

protected:
  Colour ambient_;
  ButtonRegisterType buttons_;
};

class SerialPort {
public:

  SerialPort();

  bool recvPacket(uint8_t* pkt, uint16_t len);
  bool recv(uint8_t* byte);
  bool recvNonblock(uint8_t* byte);
  bool hasPendingData() const;
  void wait(uint32_t t) const;

};

} // namespace led_driver
} // namespace zooblinkofon

