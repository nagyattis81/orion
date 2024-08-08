#pragma once

#include "engine/renderer/fade.hpp"
#include "engine/renderer/sprite.hpp"
#include <map>

using namespace std;

struct Part;

class Demo {
public:
  inline static const ivec2 SIZE = ivec2(1920, 1080);
  inline static const float ASPECT = SIZE.x / (float)SIZE.y;
  inline static const double OFFSET = 9.0;
  inline static const bool MUTE = true;
  inline static const char *MUSIC = "data/music.mp3";
  inline static const bool EDITOR = true;

private:
  inline static Demo *instance = nullptr;
  map<double, Part *> parts;
  Sprite logo;
  Fade fade;

  Demo();
  bool InitParts();

public:
  static Demo *Instance();

  bool Init();
  void Save();

  void Render(const double time);
  void End(const double time);

  void Menu();
  void Windows();

  friend struct Part01;
};