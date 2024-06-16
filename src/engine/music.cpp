#include "spdlog/spdlog.h"

#include "music.hpp"
#include <bass.h>
#include <chrono>

Music *Music::Instance() {
  if (!instance)
    instance = new Music();
  return instance;
}

Music::~Music() {
  if (handle == 0)
    return;
  BASS_ChannelStop(handle);
  BASS_Stop();
  BASS_StreamFree(handle);
  BASS_Free();
}

bool Music::Load(const Parameters &parameters) {
  if (!parameters.path) {
    spdlog::critical("invalid music path!");
    return false;
  }

  if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
    spdlog::critical("invalid bass version!");
    return false;
  }

  if (!BASS_Init(-1, 44100, 0, 0, nullptr)) {
    spdlog::critical("bass init error!");
    return false;
  }

  if (BASS_Start() == FALSE) {
    spdlog::critical("bass start error");
    return false;
  }

  handle = BASS_StreamCreateFile(false, parameters.path, 0, 0, 0);
  if (handle == 0) {
    spdlog::critical("stream create error");
    return false;
  }

  const auto length = BASS_ChannelBytes2Seconds(
      handle, BASS_ChannelGetLength(handle, BASS_POS_BYTE));
  std::chrono::seconds seconds(static_cast<int>(length));
  const auto min =
      std::chrono::duration_cast<std::chrono::minutes>(seconds).count() % 60;
  const auto sec = seconds.count() % 60;

  BASS_ChannelSetAttribute(handle, BASS_ATTRIB_VOL, parameters.volume);

  spdlog::info("MUSIC_LENGTH {}:{} volume:{}", min, sec, parameters.volume);

  return true;
}

void Music::Play() { BASS_ChannelPlay(handle, false); }

double Music::GetTime() const {
  return BASS_ChannelBytes2Seconds(
      handle, BASS_ChannelGetPosition(handle, BASS_POS_BYTE));
}

void Music::SetTime(const double time) {
  BASS_ChannelSetPosition(handle, BASS_ChannelSeconds2Bytes(handle, time),
                          BASS_POS_BYTE);
}
