#pragma once

#include "src/engine/json/object.hpp"
#include "window.hpp"

class GUI;

class Editor : public Window {
private:
  inline static Editor *instance = nullptr;

  GUI *gui = nullptr;

  Editor();
  bool Load();
  void Save();

public:
  static Editor *Instance();

  struct Settings : public json::Object {
    float scale = 1.0f;
    Settings() { Float("scale", &scale); }
  } settings;

  bool Init() override;
  void Start() override;
};