#pragma once
#include <unordered_map>
#include <stdint.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace zooblinkofon {

class AudioMixer {
public:

  AudioMixer();
  ~AudioMixer();

  bool loadSample(
      const std::string& key,
      const std::string& filename);

  void playSample(const std::string& key);

protected:
  std::unordered_map<std::string, Mix_Chunk*> samples_;
};

} // namespace zooblinkofon

