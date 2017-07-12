#pragma once
#include <stdint.h>
#include <list>
#include <functional>
#include <SDL2/SDL.h>
#include "input.h"

namespace zooblinkofon {
class AudioMixer;
class DisplayState;

struct AnimationTime {
  double t_abs;
  double t_diff;
};

using AnimationFn = std::function<void (const AnimationTime&, DisplayState*)>;

class Scene {
public:

  virtual ~Scene() = default;

  virtual void update(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio) = 0;

};

} // namespace zooblinkofon

