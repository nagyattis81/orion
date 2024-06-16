#pragma once

#include "demo.hpp"

struct Part {
  double start = -1;
  double end = -1;
  Demo *demo = nullptr;
  virtual bool Init() { return true; }
  virtual void Render(const float globalTime) = 0;
  double GetLocalTime(const float globalTime) {
    return globalTime - static_cast<float>(start);
  }
  void ClearColor(const vec3 &color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
  }
};
