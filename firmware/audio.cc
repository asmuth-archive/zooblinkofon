#include <iostream>
#include "audio.h"

namespace zooblinkofon {

void get_level_cb(int chan, void* stream, int len, void* udata) {
  auto smpl_buf = (Sint16*) stream;
  auto smpl_len = len / 4;

  if (smpl_len == 0) {
    return;
  }

  auto lvl = 0;
  for (size_t i = 1; i < smpl_len; ++i) {
    lvl += std::abs(smpl_buf[i]);
  }

  lvl /= len;

  auto linfo = static_cast<LevelInfo*>(udata);
  linfo->data[linfo->idx++ % kLevelAperture] = double(lvl) / 0x7fff;
}

AudioMixer::AudioMixer() {
  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 1, 512) != 0) {
    std::cerr << "ERROR: Mix_OpenAUdio() failed" << std::endl;
    exit(1);
  }

  Mix_RegisterEffect(MIX_CHANNEL_POST, get_level_cb, NULL, &level_);
  Mix_AllocateChannels(64);
}

AudioMixer::~AudioMixer() {
  for (auto& s : samples_) {
    Mix_FreeChunk(s.second);
  }

  Mix_CloseAudio();
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

void AudioMixer::playSample(const std::string& key, double volume /* = 0.8 */) {
  auto iter = samples_.find(key);
  if (iter == samples_.end()) {
    return;
  }

  auto chan = Mix_PlayChannel(-1, iter->second, 0);
  if (chan >= 0) {
    Mix_Volume(chan, MIX_MAX_VOLUME * volume);
  }
}

double AudioMixer::getLevel() const {
  double lvl = 0.0f;
  for (size_t i = 0; i < kLevelAperture; ++i) {
    lvl += level_.data[i];
  }

  return lvl / kLevelAperture;
}

} // namespace zooblinkofon

