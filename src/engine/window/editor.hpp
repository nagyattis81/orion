#pragma once

#include "window.hpp"

class GUI;

class Editor : public Window {
private:
  GUI *gui = nullptr;

  struct {
    float scale = 1.0f;
  } settings;

  bool Load();
  void Save();

public:
  Editor();
  bool Init() override;
  void Start() override;
};