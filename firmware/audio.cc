#include <iostream>
#include "audio.h"

namespace zooblinkofon {

AudioMixer::AudioMixer() {
  if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    std::cerr << "ERROR: SDL_Init() failed" << std::endl;
    exit(1);
  }

  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 1, 4096) != 0) {
    std::cerr << "ERROR: Mix_OpenAUdio() failed" << std::endl;
    exit(1);
  }

  Mix_AllocateChannels(64);
}

bool AudioMixer::loadSample(
    const std::string& key,
    const std::string& filename) {
  if (samples_.count(key)) {
    return false;
  }

  auto snd = Mix_LoadWAV(filename.c_str());
  if (!snd) {
    return false;
  }

  samples_.emplace(key, snd);
  return true;
}

void AudioMixer::playSample(const std::string& key) {
  auto iter = samples_.find(key);
  if (iter == samples_.end()) {
    return;
  }

  Mix_PlayChannel(-1, iter->second, 0);
}

AudioMixer::~AudioMixer() {
  for (auto& s : samples_) {
    Mix_FreeChunk(s.second);
  }

  Mix_CloseAudio();
  SDL_Quit();
}

} // namespace zooblinkofon

