#pragma once
#include <unordered_map>
#include <atomic>
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

  void playSample(const std::string& key, double volume = 0.8);

  double getLevel() const;

protected:
  std::unordered_map<std::string, Mix_Chunk*> samples_;
  std::atomic<double> level_;
};

} // namespace zooblinkofon

