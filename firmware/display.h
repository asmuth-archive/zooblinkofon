#pragma once
#include <stdint.h>
#include <array>
#include <functional>
#include <SDL2/SDL.h>

namespace zooblinkofon {
class DisplayState;

struct AnimationTime {
  double t_abs;
  double t_diff;
};

using AnimationFn = std::function<void (const AnimationTime&, DisplayState*)>;

class DisplayState {
public:
  using RGBType = std::array<uint8_t, 3>;
  using ButtonRegisterType = uint16_t;
  static const size_t kButtonCount = 10;
  static_assert(sizeof(ButtonRegisterType) * 8 >=  kButtonCount, "invalid button count");

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

class DisplayDriver {
public:

  virtual ~DisplayDriver() = default;

  virtual void render(const AnimationTime& t, DisplayState* state) = 0;

};

class VirtualDisplay : public DisplayDriver {
public:

  VirtualDisplay();
  ~VirtualDisplay();

  void render(const AnimationTime& t, DisplayState* state) override;

protected:
  SDL_Window* window_;
  SDL_Renderer* render_;
};

class HardwareDisplay : public DisplayDriver {
public:

  static const uint16_t kRefreshRateHZ = 60;

  HardwareDisplay();
  ~HardwareDisplay();

  void render(const AnimationTime& t, DisplayState* state) override;

protected:
  int serial_;
  double last_update_;
};

namespace button_animations {
AnimationFn wheel(AnimationTime t0, double speed, size_t start_index = 0);
AnimationFn wheel_negative(AnimationTime t0, double speed, size_t start_index = 0);
AnimationFn blink(size_t index, double speed);
AnimationFn linear(AnimationTime t0, double speed, size_t start_index = 0);
AnimationFn linear_negative(AnimationTime t0, double speed, size_t start_index = 0);
} // namespace button_animations

} // namespace zooblinkofon

