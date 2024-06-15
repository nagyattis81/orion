#pragma once

#include "engine/sprite.hpp"
#include <map>

struct Part;

class Demo {
private:
  std::map<double, Part *> parts;

  bool InitParts();

public:
  Sprite logo;

  inline static const int WIDTH = 1920;
  inline static const int HEIGHT = 1080;

  Demo();
  bool Init();
  bool Render(const double time);
};