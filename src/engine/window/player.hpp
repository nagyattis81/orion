#pragma once

#include "window.hpp"

class Player : public Window {
private:
  inline static Player *instance = nullptr;
  Player();

public:
  static Player *Instance();
  bool Init() override;
  void Start() override;
};