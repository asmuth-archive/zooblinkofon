#include "audio.h"
#include "display.h"
#include "scene_water.h"

namespace zooblinkofon {

scene_water::scene_water(
    const AnimationTime& t) :
    Scene(button_animations::wheel_negative(t, 5.0f)),
    atmo_sample_next_(0) {}

void scene_water::update(
    const AnimationTime& t,
    const std::list<InputEvent>& input_events,
    DisplayState* display,
    AudioMixer* audio) {
  auto audio_level = audio->getLevel();

  display->setAmbientColour(
      audio_level * 32,
      std::min(0.1 + audio_level * 8, 1.0) * 255,
      std::min(0.2 + audio_level * 3, 1.0) * 255);

  if (t.t_abs > atmo_sample_next_) {
    audio->playSample("waves", 0.5);
    atmo_sample_next_ = t.t_abs + 80;
  }

  for (const auto& e : input_events) {
    switch (e.button) {
      case InputButton::BTN0:
        playButtonAnimation(button_animations::blink(0, 8.0f), 5.0f);
        audio->playSample("duck");
        break;
      case InputButton::BTN1:
        playButtonAnimation(button_animations::blink(1, 8.0f), 4.0f);
        audio->playSample("dolphin");
        break;
      case InputButton::BTN2:
        playButtonAnimation(button_animations::blink(2, 8.0f), 6.0f);
        audio->playSample("seagull");
        break;
      case InputButton::BTN3:
        playButtonAnimation(button_animations::blink(2, 8.0f), 6.0f);
        audio->playSample("seagull");
        break;
      case InputButton::BTN4:
        playButtonAnimation(button_animations::blink(1, 8.0f), 4.0f);
        audio->playSample("dolphin");
        break;
      case InputButton::BTN5:
        playButtonAnimation(button_animations::blink(5, 8.0f), 3.0f);
        audio->playSample("duck");
        break;
      case InputButton::BTN6:
        playButtonAnimation(button_animations::blink(2, 8.0f), 6.0f);
        audio->playSample("seagull");
        break;
      case InputButton::BTN7:
        playButtonAnimation(button_animations::blink(2, 8.0f), 6.0f);
        audio->playSample("seagull");
        break;
      case InputButton::BTN8:
        playButtonAnimation(button_animations::blink(2, 8.0f), 6.0f);
        audio->playSample("seagull");
        break;
      case InputButton::BTN9:
        playButtonAnimation(button_animations::blink(1, 8.0f), 4.0f);
        audio->playSample("dolphin");
        break;
    }
  }
}


} // namespace zooblinkofon

