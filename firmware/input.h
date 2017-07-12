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

class InputHandler {
public:

  InputHandler();

  void pollInputs(std::list<InputEvent>* events);

};

} // namespace zooblinkofon

