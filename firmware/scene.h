#pragma once
#include <stdint.h>
#include <list>
#include <SDL2/SDL.h>
#include "display.h"
#include "input.h"

namespace zooblinkofon {
class AudioMixer;

class Scene {
public:

  virtual ~Scene() = default;

  virtual void update(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio) = 0;

protected:
  AnimationFn button_anim_;
};

} // namespace zooblinkofon

