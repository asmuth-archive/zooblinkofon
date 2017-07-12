#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "audio.h"
#include "display.h"
#include "input.h"
#include "scene.h"
#include "scene_farm.h"

using namespace zooblinkofon;

int main() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
    std::cerr << "ERROR: SDL_Init() failed" << std::endl;
    exit(1);
  }

  AudioMixer audio;
  if (!audio.loadSample("notify", "media/notify.wav")) {
    std::cerr << "ERROR: error while loading sample" << std::endl;
    return 1;
  }

  InputHandler input;
  DisplayState display;
  VirtualDisplay virtual_display;

  std::unique_ptr<Scene> scene(new scene_farm());;
  for (size_t n = 0; ; ++n) {
    AnimationTime t;
  
    std::list<InputEvent> input_events;
    input.pollInputs(&input_events);

    for (const auto& e : input_events) {
      if (e.button == InputButton::QUIT) {
        exit(0);
      }
    }

    scene->update(t, input_events, &display, &audio);
    virtual_display.render(&display);

    usleep(20000);
  }

  SDL_Quit();
  return 0;
}

