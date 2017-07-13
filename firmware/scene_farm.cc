#include "audio.h"
#include "display.h"
#include "scene_farm.h"

namespace zooblinkofon {

scene_farm::scene_farm(
    const AnimationTime& t) :
    Scene(button_animations::wheel_negative(t, 5.0f)) {}

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
      case InputButton::BTN1:
        playButtonAnimation(button_animations::blink(1, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN2:
        playButtonAnimation(button_animations::blink(2, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN3:
        playButtonAnimation(button_animations::blink(3, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN4:
        playButtonAnimation(button_animations::blink(4, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN5:
        playButtonAnimation(button_animations::blink(5, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN6:
        playButtonAnimation(button_animations::blink(6, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN7:
        playButtonAnimation(button_animations::blink(7, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN8:
        playButtonAnimation(button_animations::blink(8, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
      case InputButton::BTN9:
        playButtonAnimation(button_animations::blink(9, 8.0f), 1.0f);
        audio->playSample("notify");
        break;
    }
  }
}


} // namespace zooblinkofon

