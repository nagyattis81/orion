#pragma once

#include "engine/fade.hpp"
#include "engine/sprite.hpp"
#include <map>

using namespace glm;

struct Part;

struct Demo {
  Sprite logo;
  Fade fade;

  std::map<double, Part *> CreateParts();
  bool Init();
  void Render(const double time);
};