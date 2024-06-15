#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "part.hpp"

extern Part *CreatePart01(const glm::vec3& clearColor);

Demo::Demo() {
  parts[10.0] = CreatePart01(glm::vec3(1.0f, 0.0f, 0.0f));
  parts[20.0] = CreatePart01(glm::vec3(0.0f, 1.0f, 0.0f));
  parts[30.0] = CreatePart01(glm::vec3(0.0f, 0.0f, 1.0f));
}

bool Demo::Init() {
  spdlog::info("!!! Demo init");

  if (!logo.Load({.fileName = "data/textures/cover_1.jpg", .flip = false}))
    return false;

  return InitParts();
}

bool Demo::InitParts() {
  double start = 0;
  for (auto it : parts) {
    spdlog::info("*** Part {} init", it.first);
    if (!it.second->Init())
      return false;
    it.second->start = start;
    it.second->end = it.first;
    start = it.first;
    it.second->demo = this;
  }
  return true;
}

bool Demo::Render(const double time) {
  double end = 0.0;
  for (auto it : parts) {
    if (it.second->start < time && time < it.second->end) {
      it.second->Render(static_cast<float>(time));
      end = it.second->end;
    }
  }
  if (end < time)
    return true;
  return false;
}
