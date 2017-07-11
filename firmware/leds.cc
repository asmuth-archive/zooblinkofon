#include "leds.h"

namespace zooblinkofon {

LEDMixer::LEDMixer() : ambient_colour_{0, 0, 0} {
  for (size_t i = 0; i < kButtonCount; ++i) {
    buttons_[i] = false;
  }
}

bool LEDMixer::getButton(size_t index) const {
  return buttons_[index];
}

void LEDMixer::setButton(size_t index, bool state) {
  buttons_[index] = state;
}

const LEDMixer::RGBType& LEDMixer::getAmbientColour() const {
  return ambient_colour_;
}

void LEDMixer::setAmbientColour(RGBType colour) {
  ambient_colour_ = colour;
}

void LEDMixer::setAmbientColour(
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  setAmbientColour(RGBType{red, green, blue});
}

} // namespace zooblinkofon

