#pragma once
#include "scene.h"

namespace zooblinkofon {

class scene_water : public Scene {
public:

  scene_water(const AnimationTime& t);

  void update(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio) override;

private:
  AnimationFn button_anim_;
  double atmo_sample_next_;
};

} // namespace zooblinkofon

