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

  Scene(AnimationFn button_anim_default);
  virtual ~Scene() = default;

  void updateScene(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio);

  virtual void update(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio) = 0;

  void playButtonAnimation(AnimationFn anim, double duration = 0.0f);

private:
  AnimationFn button_anim_default_;
  AnimationFn button_anim_;
  double button_anim_duration_;
};

} // namespace zooblinkofon

