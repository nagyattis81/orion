#pragma once

#include "./../demo.hpp"
#include "parameters/parameters.hpp"
#include <imgui.h>

struct Part {
  const char *name = nullptr;
  double start = -1;
  double end = -1;
  Demo *demo = nullptr;
  bool showWindow = false;

  Parameters parameters = Parameters("part");

  Part(const char *name, const bool showWindow)
      : name(name), showWindow(showWindow) {
    parameters.name = name;
  }

  virtual bool Init() { return true; }
  virtual void Render(const float globalTime) = 0;

  double GetLocalTime(const float globalTime) {
    return globalTime - static_cast<float>(start);
  }
  void ClearColor(const vec3 &color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
  }
};
