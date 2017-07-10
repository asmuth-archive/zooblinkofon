#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "input.h"
#include "audio.h"

using namespace zooblinkofon;

int main() {
  InputHandler input;

  AudioMixer audio;
  if (!audio.loadSample("notify", "media/notify.wav")) {
    std::cerr << "ERROR: error while loading sample" << std::endl;
    return 1;
  }

  for (;;) {
    std::list<InputEvent> input_events;
    input.pollInputs(&input_events);

    for (const auto& e : input_events) {
      std::cerr << "EVENT: " << e.button << std::endl;
      if (e.button == 4) {
        audio.playSample("notify");
      }
    }
  }

  return 0;
}

