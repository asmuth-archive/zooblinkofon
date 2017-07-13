#include "scene.h"

namespace zooblinkofon {

Scene::Scene(
    AnimationFn button_anim_default) :
    button_anim_default_(button_anim_default),
    button_anim_(button_anim_default) {}

void Scene::updateScene(
    const AnimationTime& t,
    const std::list<InputEvent>& input_events,
    DisplayState* display,
    AudioMixer* audio) {
  if (button_anim_duration_ > 0.0f) {
    button_anim_duration_ -= t.t_diff;
  } else {
    button_anim_ = button_anim_default_;
    button_anim_duration_ = 0.0f;
  }

  button_anim_(t, display);
  update(t, input_events, display, audio);
}

void Scene::playButtonAnimation(AnimationFn anim, double duration /* = 0.0f */) {
  button_anim_ = anim;
  button_anim_duration_ = duration;
}

} // namespace zooblinkofon

