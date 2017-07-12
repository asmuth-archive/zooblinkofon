#pragma once
#include <stdint.h>
#include <array>
#include <SDL2/SDL.h>

namespace zooblinkofon {

class DisplayState {
public:
  using RGBType = std::array<uint8_t, 3>;
  using ButtonRegisterType = uint16_t;
  static const size_t kButtonCount = sizeof(ButtonRegisterType) * 8;

  DisplayState();

  bool getButton(size_t index) const;
  void setButton(size_t index, bool state);

  const RGBType& getAmbientColour() const;
  void setAmbientColour(RGBType colour);
  void setAmbientColour(
      uint8_t red,
      uint8_t green,
      uint8_t blue);

protected:
  std::array<bool, kButtonCount> buttons_;
  RGBType ambient_colour_;
};

class VirtualDisplay {
public:

  VirtualDisplay();
  ~VirtualDisplay();

  void render(DisplayState* state);

protected:
  SDL_Window* window_;
  SDL_Renderer* render_;
};

} // namespace zooblinkofon

