#pragma once
#include <unordered_map>
#include <stdint.h>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace zooblinkofon {

enum InputEventType { KEYDOWN, KEYUP };

struct InputEvent {
  InputEventType type;
  size_t button;
};

class InputHandler {
public:

  InputHandler();

  void pollInputs(std::list<InputEvent>* events);

};

} // namespace zooblinkofon

