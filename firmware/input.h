#pragma once
#include <unordered_map>
#include <stdint.h>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "display.h"

namespace zooblinkofon {

enum class InputAction { KEYDOWN, KEYUP };
enum class InputButton{
  BTN0,
  BTN1,
  BTN2,
  BTN3,
  BTN4,
  BTN5,
  BTN6,
  BTN7,
  BTN8,
  BTN9,
  QUIT
};

struct InputEvent {
  InputAction action;
  InputButton button;
};

class InputDevice {
public:

  virtual ~InputDevice() = default;

  virtual void pollInputs(const AnimationTime& t, std::list<InputEvent>* events) = 0;

};

class VirtualInputDevice : public InputDevice {
public:

  VirtualInputDevice();

  void pollInputs(const AnimationTime& t, std::list<InputEvent>* events) override;

};

class HardwareInputDevice : public InputDevice {
public:

  HardwareInputDevice();
  ~HardwareInputDevice();

  void pollInputs(const AnimationTime& t, std::list<InputEvent>* events) override;

protected:
  struct ButtonState {
    bool pressed;
    double time;
  };

  volatile void* gpio_;
  std::array<ButtonState, DisplayState::kButtonCount> buttons_;
};

} // namespace zooblinkofon

