#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "input.h"
#include "audio.h"
#include "leds.h"
#include "monitor.h"

using namespace zooblinkofon;

int main() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
    std::cerr << "ERROR: SDL_Init() failed" << std::endl;
    exit(1);
  }

  InputHandler input;
  LEDMixer leds;

  AudioMixer audio;
  if (!audio.loadSample("notify", "media/notify.wav")) {
    std::cerr << "ERROR: error while loading sample" << std::endl;
    return 1;
  }

  DebugMonitor monitor(&leds);

  for (size_t n = 0; ; ++n) {
    std::list<InputEvent> input_events;
    input.pollInputs(&input_events);

    for (const auto& e : input_events) {
      std::cerr << "EVENT: " << e.button << std::endl;
      if (e.button == 4) {
        audio.playSample("notify");
      }
    }

    leds.setAmbientColour(n % 255, 0, 255 - (n % 255));

    for (size_t i = 0; i < LEDMixer::kButtonCount; ++i) {
      leds.setButton(i, (n / 10) % LEDMixer::kButtonCount == i);
    }

    monitor.refresh();
    usleep(20000);
  }

  SDL_Quit();
  return 0;
}

