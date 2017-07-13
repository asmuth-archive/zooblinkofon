#pragma once
#include <unordered_map>
#include <stdint.h>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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

  virtual void pollInputs(std::list<InputEvent>* events) = 0;

};

class VirtualInputDevice : public InputDevice {
public:

  VirtualInputDevice();

  void pollInputs(std::list<InputEvent>* events) override;

};

class HardwareInputDevice : public InputDevice {
public:

  HardwareInputDevice();
  ~HardwareInputDevice();

  void pollInputs(std::list<InputEvent>* events) override;

protected:
  volatile void* gpio_;
};

} // namespace zooblinkofon

