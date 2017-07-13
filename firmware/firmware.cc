#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <ctime>
#include <sys/time.h>
#include <sys/types.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#include "audio.h"
#include "display.h"
#include "input.h"
#include "scene.h"
#include "scene_farm.h"

using namespace zooblinkofon;

static const uint64_t kRefreshRateHZ = 500;

static const std::vector<std::pair<std::string, std::string>> kAudioSamples = {
  { "rooster", "media/rooster.wav" },
  { "goat", "media/goat.wav" },
  { "duck", "media/duck.wav" },
  { "birds1", "media/birds1.wav" },
  { "birds2", "media/birds2.wav" },
  { "birds3", "media/birds3.wav" },
  { "cow1", "media/cow1.wav" },
  { "cow2", "media/cow2.wav" },
  { "chicken", "media/chicken.wav" },
};

double get_tick() {
#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  return double(mts.tv_sec) + mts.tv_nsec / 1000000000.0f;
#else
  timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    std::cerr << "clock_gettime(CLOCK_MONOTONIC) failed\n";
    abort();
  } else {
    return double(ts.tv_sec) + ts.tv_nsec / 1000000000.0f;
  }
#endif
}

int main() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
    std::cerr << "ERROR: SDL_Init() failed" << std::endl;
    exit(1);
  }

  AudioMixer audio;
  for (const auto& a : kAudioSamples) {
    if (!audio.loadSample(a.first, a.second)) {
      std::cerr << "ERROR: error while loading sample: " << a.second << std::endl;
      return 1;
    }
  }

  InputHandler input;
  DisplayState display;
  VirtualDisplay virtual_display;

  AnimationTime t{ .t_abs = 0, .t_diff = 0 };
  std::unique_ptr<Scene> scene(new scene_farm(t));;
  for (auto t0 = get_tick(); ; ) {
    auto t_start = get_tick() - t0;
    t.t_diff = t_start - t.t_abs;
    t.t_abs = t_start;

    std::list<InputEvent> input_events;
    input.pollInputs(&input_events);

    for (const auto& e : input_events) {
      if (e.button == InputButton::QUIT) {
        exit(0);
      }
    }

    //printf("t_abs=%f, t_diff=%f, freq=%f\r", t.t_abs, t.t_diff, 1.0f / t.t_diff);
    scene->updateScene(t, input_events, &display, &audio);
    virtual_display.render(&display);

    auto t_loop = (get_tick() - t0) - t_start;
    if (t_loop < 1.0f / kRefreshRateHZ) {
      usleep(((1.0f / kRefreshRateHZ) - t_loop) * 1000000);
    }
  }

  SDL_Quit();
  return 0;
}

