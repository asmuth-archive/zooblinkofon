#pragma once
#include "scene.h"

namespace zooblinkofon {

class scene_farm : public Scene {
public:

  scene_farm();

  void update(
      const AnimationTime& t,
      const std::list<InputEvent>& input_events,
      DisplayState* display,
      AudioMixer* audio) override;

private:
  AnimationFn button_anim_;
};

} // namespace zooblinkofon

