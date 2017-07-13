#include "led_driver.h"
#include "vendor/light_ws2812.h"

namespace zooblinkofon {
namespace led_driver {

const uint8_t LEDDriver::kButtonMap[] = {
  6,
  4,
  2,
  5,
  3,
  12,
  10,
  11,
  14,
  13
};

LEDDriver::LEDDriver() : buttons_(0) {
  ambient_.r = 0;
  ambient_.g = 0;
  ambient_.b = 0;

  DDRD |= 1 << kButtonDataPin;
  DDRD |= 1 << kButtonClockPin;
  DDRD |= 1 << kButtonLatchPin;
}

void LEDDriver::setButton(uint8_t index, bool state) {
  if (state) {
    buttons_ |= 1 << kButtonMap[index];
  } else {
    buttons_ &= ~(1 << kButtonMap[index]);
  }
}

void LEDDriver::setAmbientColour(const Colour& c) {
  ambient_ = c;
}

void LEDDriver::setAmbientColour(
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  Colour c;
  c.r = red;
  c.g = green;
  c.b = blue;

  setAmbientColour(c);
}

static void setp(int p, int s) {
  if (s) {
    PORTD |= (1 << p);
  } else {
    PORTD &= ~(1 << p);
  }
}

void LEDDriver::refreshDisplay() {
  // write ws2812 data
  cli();
  ws2812_setleds(&ambient_, 32);
  sei();

  // write buttons to shift register
  setp(kButtonLatchPin, 0);

  for (uint8_t i = 0; i < kButtonCount; ++i) {
    setp(kButtonClockPin, 0);
    setp(kButtonDataPin, buttons_ & (1 << i));
    _delay_us(10);
    setp(kButtonClockPin, 1);
    _delay_us(10);
  }

  setp(kButtonLatchPin, 1);
}

void LEDDriver::clear() {
  buttons_ = 0;
  setAmbientColour(0, 0, 0);
  refreshDisplay();
}

SerialPort::SerialPort() {
  UBRR0L = 0x19;
  UBRR0H = 0;
  UCSR0B = (1 << RXEN0);
  UCSR0C = (3 << UCSZ00);
}

bool SerialPort::recvPacket(uint8_t* pkt, uint16_t len) {
  for (uint8_t i = 0; i < len; ++i) {
    if (!recv(&pkt[i])) {
      return false;
    }
  }

  return true;
}

bool SerialPort::recv(uint8_t* byte) {
  for (uint32_t i = 0; i < F_CPU / 16384; ++i) {
    if (UCSR0A & (1 << RXC0)) {
      *byte = UDR0;
      return true;
    }
  }

  return false;
}

bool SerialPort::recvNonblock(uint8_t* byte) {
  if (hasPendingData()) {
    *byte = UDR0;
    return true;
  } else {
    return false;
  }
}

bool SerialPort::hasPendingData() const {
  return UCSR0A & (1 << RXC0);
}

void SerialPort::wait(uint32_t t) const {
  for (uint32_t i = 0; i < t * (F_CPU / 16384) && !(UCSR0A & (1 << RXC0)); ++i);
}

static const uint8_t kPacketLength = 5;
SerialPort serial_port;
LEDDriver led_driver;

void bootanim() {
  led_driver.clear();

  for (uint8_t n = 0; n < 5; n++) {
    led_driver.setButton(4 - n, 1);
    led_driver.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = (n * 50) + i;
      led_driver.setAmbientColour(b, b, b);
      led_driver.refreshDisplay();
      _delay_ms(5);
    }
  }

  for (uint8_t n = 0; n < 5; n++) {
    led_driver.setButton(4 - n, 1);
    led_driver.setButton((4 - n) + 5, 1);
    for (uint8_t i = 0; i < 50; ++i) {
      auto b = 250 - ((n * 50) + i);
      led_driver.setAmbientColour(b, b, b);
      led_driver.refreshDisplay();
      _delay_ms(5);
    }
  }

  led_driver.setAmbientColour(0, 0, 0);
  led_driver.refreshDisplay();
}

void idleanim() {
  led_driver.clear();

  while (!serial_port.hasPendingData()) {
    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_driver.setButton(4 - n, 0);
      led_driver.setButton((4 - n) + 5, 0);
      led_driver.refreshDisplay();
      serial_port.wait(200);
    }

    for (uint8_t n = 0; n < 5; n++) {
      if (serial_port.hasPendingData()) {
        break;
      }

      led_driver.setButton(4 - n, 1);
      led_driver.setButton((4 - n) + 5, 1);
      led_driver.refreshDisplay();
      serial_port.wait(200);
    }
  }
}

void update(uint8_t* pkt) {
  auto buttons = uint16_t(pkt[3]) | (uint16_t(pkt[4]) << 8);
  led_driver.setButton(0, buttons & (1 << 0));
  led_driver.setButton(1, buttons & (1 << 1));
  led_driver.setButton(2, buttons & (1 << 2));
  led_driver.setButton(3, buttons & (1 << 3));
  led_driver.setButton(4, buttons & (1 << 4));
  led_driver.setButton(5, buttons & (1 << 5));
  led_driver.setButton(6, buttons & (1 << 6));
  led_driver.setButton(7, buttons & (1 << 7));
  led_driver.setButton(8, buttons & (1 << 8));
  led_driver.setButton(9, buttons & (1 << 9));
  led_driver.setAmbientColour(pkt[0], pkt[1], pkt[2]);
  led_driver.refreshDisplay();
}

void entry() {
  bootanim();

  for (;;) {
    idleanim();

    for (uint32_t timeout = 0; timeout < (F_CPU / 8192); ++timeout) {
      uint8_t pkt[kPacketLength];
      if (serial_port.recvPacket(pkt, sizeof(pkt))) {
        update(pkt);
        timeout = 0;
      }
    }
  }
}

} // namespace led_driver
} // namespace zooblinkofon

int main(void) {
  zooblinkofon::led_driver::entry();
  return 0;
}

