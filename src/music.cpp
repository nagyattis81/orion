#include "music.hpp"
#include <bass.h>
#include <chrono>
#include <iostream>

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

bool Music::Load(const char *path) {
  if (!path) {
    std::cerr << "invalid music path!";
    return false;
  }

  if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
    std::cerr << "invalid bass version!";
    return false;
  }

  if (!BASS_Init(-1, 44100, 0, 0, nullptr)) {
    std::cerr << "bass init error!";
    return false;
  }

  if (BASS_Start() == FALSE) {
    std::cerr << "bass start error";
    return false;
  }

  handle = BASS_StreamCreateFile(false, path, 0, 0, 0);
  if (handle == 0) {
    std::cerr << "stream create error";
    return false;
  }

  const auto length = BASS_ChannelBytes2Seconds(
      handle, BASS_ChannelGetLength(handle, BASS_POS_BYTE));
  std::chrono::seconds seconds(static_cast<int>(length));
  const auto min =
      std::chrono::duration_cast<std::chrono::minutes>(seconds).count() % 60;
  const auto sec = seconds.count() % 60;

  std::cout << "MUSIC_LENGTH " << min << ":" << sec << std::endl;

  return true;
}

void Music::Play() { BASS_ChannelPlay(handle, false); }

double Music::GetTime() const {
  return BASS_ChannelBytes2Seconds(
      handle, BASS_ChannelGetPosition(handle, BASS_POS_BYTE));
}
