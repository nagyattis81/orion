#include "part.hpp"

Part::Part(const char *name) : name(name) { parameter.name = name; }

bool Part::Load() { return parameter.LoadFromFile(); }

void Part::Save() { parameter.SaveToFile(); }

double Part::GetLocalTime(const float globalTime) {
  return globalTime - static_cast<float>(start);
}

void Part::ClearColor(const vec3 &color) {
  glClearColor(color.r, color.g, color.b, 1.0f);
}

void Part::GUI() { parameter.GUI(); }
