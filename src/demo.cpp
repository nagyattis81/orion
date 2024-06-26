#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "part.hpp"
#include <imgui.h>

extern Part *CreatePart01();
extern Part *CreatePart02();

Demo *Demo::Instance() {
  if (!instance)
    instance = new Demo();
  return instance;
}

Demo::Demo() {
  parts[9.0] = CreatePart01();
  parts[60.0] = CreatePart02();
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

void Demo::Begin(const double time) {
  // TODO
}

void Demo::Render(const double time) {
  for (auto it : parts)
    if (it.second->start <= time && time < it.second->end)
      it.second->Render(static_cast<float>(time));
}

void Demo::End(const double time) { fade.Render(time); }

void Demo::Menu() {
  for (auto it : parts) {
    Part *part = it.second;
    if (ImGui::MenuItem(part->Name(), nullptr, part->showWindow))
      part->showWindow = !part->showWindow;
  }
}

void Demo::Windows() {
  for (auto it : parts) {
    Part *part = it.second;
    if (!part->showWindow)
      continue;
    if (ImGui::Begin(part->Name(), &part->showWindow)) {
      part->GUI();
      ImGui::End();
    }
  }
}
