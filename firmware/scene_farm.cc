#include "display.h"
#include "scene_farm.h"

namespace zooblinkofon {

scene_farm::scene_farm() : button_anim_(button_animations::negative_wheel(5.0f)) {}

void scene_farm::update(
    const AnimationTime& t,
    const std::list<InputEvent>& input_events,
    DisplayState* display,
    AudioMixer* audio) {
  button_anim_(t, display);
}

} // namespace zooblinkofon

