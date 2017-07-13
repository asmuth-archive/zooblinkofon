#include "audio.h"
#include "display.h"
#include "scene_farm.h"

namespace zooblinkofon {

scene_farm::scene_farm() : Scene(button_animations::negative_wheel(5.0f)) {}

void scene_farm::update(
    const AnimationTime& t,
    const std::list<InputEvent>& input_events,
    DisplayState* display,
    AudioMixer* audio) {
  for (const auto& e : input_events) {
    switch (e.button) {
      case InputButton::BTN0:
        playButtonAnimation(button_animations::blink(0, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
    }
  }
}


} // namespace zooblinkofon

