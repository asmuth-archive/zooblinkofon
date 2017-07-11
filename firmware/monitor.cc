#include "monitor.h"
#include "leds.h"

namespace zooblinkofon {

DebugMonitor::DebugMonitor(LEDMixer* led_mixer) : led_mixer_(led_mixer) {
  window_ = SDL_CreateWindow(
      "the zooblinkofon debug monitor",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      1200,
      730,
      SDL_WINDOW_SHOWN);

  render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

DebugMonitor::~DebugMonitor() {
  SDL_DestroyWindow(window_);
}

void DebugMonitor::refresh() {
  auto ambient = led_mixer_->getAmbientColour();
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

    if (led_mixer_->getButton(i)) {
      SDL_SetRenderDrawColor(render_, 255, 255, 255, 255);
    } else {
      SDL_SetRenderDrawColor(render_, 60, 60, 60, 255);
    }

    SDL_RenderFillRect(render_, &r);
  }

  SDL_RenderPresent(render_);
}

} // namespace zooblinkofon

