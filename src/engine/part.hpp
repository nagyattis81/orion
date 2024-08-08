#pragma once

#include "parameter/parameter.hpp"
#include "src/demo.hpp"

struct Part {
  const char *name = nullptr;
  double start = -1;
  double end = -1;
  Demo *demo = nullptr;
  Parameter parameter;

  Part(const char *name);
  bool Load();
  void Save();
  double GetLocalTime(const float globalTime);
  void ClearColor(const vec3 &color);
  void GUI();

  virtual bool Init() { return true; }
  virtual void Render(const float globalTime) = 0;
};
