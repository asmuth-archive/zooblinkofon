#include "display.h"

namespace zooblinkofon {

DisplayState::DisplayState() : ambient_colour_{0, 0, 0} {
  for (size_t i = 0; i < kButtonCount; ++i) {
    buttons_[i] = false;
  }
}

bool DisplayState::getButton(size_t index) const {
  return buttons_[index];
}

void DisplayState::setButton(size_t index, bool state) {
  buttons_[index] = state;
}

const DisplayState::RGBType& DisplayState::getAmbientColour() const {
  return ambient_colour_;
}

void DisplayState::setAmbientColour(RGBType colour) {
  ambient_colour_ = colour;
}

void DisplayState::setAmbientColour(
    uint8_t red,
    uint8_t green,
    uint8_t blue) {
  setAmbientColour(RGBType{red, green, blue});
}

VirtualDisplay::VirtualDisplay() {
  window_ = SDL_CreateWindow(
      "the zooblinkofon debug monitor",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      1200,
      730,
      SDL_WINDOW_SHOWN);

  render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

VirtualDisplay::~VirtualDisplay() {
  SDL_DestroyWindow(window_);
}

void VirtualDisplay::render(DisplayState* display) {
  auto ambient = display->getAmbientColour();
  SDL_SetRenderDrawColor(render_, 42, 42, 42, 255);
  SDL_RenderClear(render_);

  {
    SDL_Rect r;
    r.x = 150;
    r.y = 50;
    r.w = 900;
    r.h = 630;

    SDL_SetRenderDrawColor(render_, ambient[0], ambient[1], ambient[2], 255);
    SDL_RenderFillRect(render_, &r);
  }

  for (size_t i = 0; i < 10; ++i) {
    SDL_Rect r;
    r.x = i < 5 ? 50 : 1100;
    r.y = 100 + (i % 5) * 120;
    r.w = 50;
    r.h = 50;

    if (display->getButton(i)) {
      SDL_SetRenderDrawColor(render_, 255, 255, 255, 255);
    } else {
      SDL_SetRenderDrawColor(render_, 60, 60, 60, 255);
    }

    SDL_RenderFillRect(render_, &r);
  }

  SDL_RenderPresent(render_);
}

HardwareDisplay::HardwareDisplay() {}
HardwareDisplay::~HardwareDisplay() {}
void HardwareDisplay::render(DisplayState* display) {}

namespace button_animations {

AnimationFn wheel(AnimationTime t0, double speed, size_t start_index /* = 0 */) {
  return [=] (const AnimationTime& t, DisplayState* display) {
    uint64_t seq = ((t.t_abs - t0.t_abs) * speed) + start_index;

    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      display->setButton(i, seq % DisplayState::kButtonCount == i);
    }
  };
}

AnimationFn wheel_negative(AnimationTime t0, double speed, size_t start_index /* = 0 */) {
  return [=] (const AnimationTime& t, DisplayState* display) {
    uint64_t seq = ((t.t_abs - t0.t_abs) * speed) + start_index;

    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      display->setButton(i, seq % DisplayState::kButtonCount != i);
    }
  };
}

AnimationFn blink(size_t index, double speed) {
  return [index, speed] (const AnimationTime& t, DisplayState* display) {
    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      display->setButton(
        i,
        i == index ? uint64_t(t.t_abs * speed) % 2 : false);
    }
  };
}

AnimationFn linear(AnimationTime t0, double speed, size_t start_index /* = 0 */) {
  return [=] (const AnimationTime& t, DisplayState* display) {
    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      uint64_t seq = ((t.t_abs - t0.t_abs) * speed) + start_index;

      display->setButton(
          i,
          seq % (DisplayState::kButtonCount / 2) == i % (DisplayState::kButtonCount / 2));
    }
  };
}

AnimationFn linear_negative(AnimationTime t0, double speed, size_t start_index /* = 0 */) {
  return [=] (const AnimationTime& t, DisplayState* display) {
    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      uint64_t seq = ((t.t_abs - t0.t_abs) * speed) + start_index;

      display->setButton(
          i,
          seq % (DisplayState::kButtonCount / 2) != i % (DisplayState::kButtonCount / 2));
    }
  };
}

} // namespace button_animations

} // namespace zooblinkofon

