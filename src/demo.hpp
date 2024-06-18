#pragma once

#include "engine/fade.hpp"
#include "engine/sprite.hpp"
#include <map>

using namespace std;

struct Part;

struct Demo {
  Sprite logo;
  Fade fade;

  map<double, Part *> CreateParts();
  bool Init();
  void Render(const double time);
};