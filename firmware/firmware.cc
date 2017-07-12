#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "audio.h"
#include "display.h"
#include "input.h"

using namespace zooblinkofon;

int main() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
    std::cerr << "ERROR: SDL_Init() failed" << std::endl;
    exit(1);
  }

  InputHandler input;
  DisplayState display;
  VirtualDisplay virtual_display;

  AudioMixer audio;
  if (!audio.loadSample("notify", "media/notify.wav")) {
    std::cerr << "ERROR: error while loading sample" << std::endl;
    return 1;
  }

  for (size_t n = 0; ; ++n) {
    std::list<InputEvent> input_events;
    input.pollInputs(&input_events);

    for (const auto& e : input_events) {
      std::cerr << "EVENT: " << e.button << std::endl;
      if (e.button == 4) {
        audio.playSample("notify");
      }
    }

    display.setAmbientColour(n % 255, 0, 255 - (n % 255));

    for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
      display.setButton(i, (n / 10) % DisplayState::kButtonCount == i);
    }

    virtual_display.render(&display);
    usleep(20000);
  }

  SDL_Quit();
  return 0;
}

