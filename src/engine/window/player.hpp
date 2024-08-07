#pragma once

#include "window.hpp"

class Player : public Window {
public:
  bool Init() override;
  void Start() override;
};