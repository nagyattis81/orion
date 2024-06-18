#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "part.hpp"

extern Part *CreatePart01();
extern Part *CreatePart02();

map<double, Part *> Demo::CreateParts() {
  map<double, Part *> parts;
  parts[9.0] = CreatePart01();
  parts[60.0] = CreatePart02();
  return parts;
}

bool Demo::Init() {
  if (!logo.Load({.fileName = "data/textures/cover_1.jpg", .flip = false}))
    return false;
  if (!fade.Init())
    return false;
  fade.animation.Push(0.0, 1.0f);
  fade.animation.Push(1.0, 0.0f);
  fade.animation.Push(8.75, 0.0f);
  fade.animation.Push(9.0, 1.0f);
  fade.animation.Push(9.25, 0.0f);
  fade.animation.Push(59.0, 0.0f);
  fade.animation.Push(60.0, 1.0f);
  return true;
}

void Demo::Render(const double time) { fade.Render(time); }
