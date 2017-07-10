#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "audio_mixer.h"

using namespace zooblinkofon;

int main() {
  AudioMixer audio;
  if (!audio.loadSample("notify", "media/notify.wav")) {
    std::cerr << "ERROR: error while loading sample" << std::endl;
    return 1;
  }

  for (;;) {
    audio.playSample("notify");
    usleep(200 * 1000);
  }

  return 0;
}

