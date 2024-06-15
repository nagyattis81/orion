#pragma once

#include "demo.hpp"

struct Part {
  double start = -1;
  double end = -1;
  Demo *demo = nullptr;
  virtual bool Init() { return true; }
  virtual void Render(const double globalTime) = 0;
  double GetLocalTime(const double globalTime) { return globalTime - start; }
};
