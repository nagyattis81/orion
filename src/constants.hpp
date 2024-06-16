#pragma once

#include <glm/vec2.hpp>

using namespace glm;

struct Constants {
  inline static const ivec2 SIZE = ivec2(1920, 1080);
  inline static const float ASPECT = SIZE.x / (float)SIZE.y;
  inline static const double OFFSET = 0.0;
  inline static const bool TITLE_TIME = true;
  inline static const bool MUTE = true;
  inline static const char *MUSIC = "data/music.mp3";
};
