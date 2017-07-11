#pragma once
#include <unordered_map>
#include <stdint.h>
#include <string>
#include <SDL2/SDL.h>

namespace zooblinkofon {
class LEDMixer;

class DebugMonitor {
public:

  DebugMonitor(LEDMixer* led_mixer);
  ~DebugMonitor();

  void refresh();

protected:
  LEDMixer* led_mixer_;
  SDL_Window* window_;
  SDL_Renderer* render_;
};

} // namespace zooblinkofon

