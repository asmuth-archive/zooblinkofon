#include "audio.h"
#include "display.h"
#include "scene_farm.h"

namespace zooblinkofon {

scene_farm::scene_farm(
    const AnimationTime& t) :
    Scene(button_animations::wheel_negative(t, 5.0f)),
    atmo_sample_next_(0) {}

void scene_farm::update(
    const AnimationTime& t,
    const std::list<InputEvent>& input_events,
    DisplayState* display,
    AudioMixer* audio) {
  auto audio_level = audio->getLevel();

  display->setAmbientColour(
      std::min(0.3 + audio_level * 4, 1.0) * 255,
      std::min(0.5 + audio_level * 3, 1.0) * 255,
      audio_level * 0);

  if (t.t_abs > atmo_sample_next_) {
    auto r = random() % 34;
    if (r > 0 && r < 10) {
      audio->playSample("birds1", 0.1);
    } else if (r > 10 && r < 20)  {
      audio->playSample("birds2", 0.3);
    } else if (r > 20 && r < 30)  {
      audio->playSample("birds3", 0.1);
    } else if (r == 30) {
      audio->playSample("rooster", 0.4);
    } else if (r == 31) {
      audio->playSample("duck", 0.6);
    } else if (r == 32) {
      audio->playSample("cow2", 0.2);
    } else if (r == 32) {
      audio->playSample("chicken", 0.3);
    }

    atmo_sample_next_ = t.t_abs + random() % 5;
  }

  for (const auto& e : input_events) {
    switch (e.button) {
      case InputButton::BTN0:
        playButtonAnimation(button_animations::blink(0, 8.0f), 1.9f);
        audio->playSample("rooster");
        break;
      case InputButton::BTN1:
        playButtonAnimation(button_animations::blink(1, 8.0f), 4.0f);
        audio->playSample("goat");
        break;
      case InputButton::BTN2:
        playButtonAnimation(button_animations::blink(2, 8.0f), 5.0f);
        audio->playSample("duck");
        break;
      case InputButton::BTN3:
        playButtonAnimation(button_animations::blink(3, 8.0f), 3.0f);
        audio->playSample("cow1");
        break;
      case InputButton::BTN4:
        playButtonAnimation(button_animations::blink(4, 8.0f), 8.0f);
        audio->playSample("chicken");
        break;
      case InputButton::BTN5:
        playButtonAnimation(button_animations::blink(5, 8.0f), 3.0f);
        audio->playSample("elephant");
        break;
      case InputButton::BTN6:
        playButtonAnimation(button_animations::blink(6, 8.0f), 3.0f);
        audio->playSample("monkeys");
        break;
      case InputButton::BTN7:
        playButtonAnimation(button_animations::blink(7, 8.0f), 4.5f);
        audio->playSample("peacock", 0.5);
        break;
      case InputButton::BTN8:
        playButtonAnimation(button_animations::blink(8, 8.0f), 1.0f);
        audio->playSample("sheep");
        break;
      case InputButton::BTN9:
        playButtonAnimation(button_animations::blink(9, 8.0f), 6.0f);
        audio->playSample("pigs", 0.5);
        break;
    }
  }
}


} // namespace zooblinkofon

