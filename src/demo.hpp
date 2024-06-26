#pragma once

#include "engine/fade.hpp"
#include "engine/sprite.hpp"
#include <map>

using namespace std;

struct Part;

class Demo {
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

  void Begin(const double time);
  void Render(const double time);
  void End(const double time);

  void Menu();
  void Windows();

  friend struct Part01;
};