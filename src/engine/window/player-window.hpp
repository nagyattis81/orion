#pragma once

#include "window.hpp"

class PlayerWindow : public Window {
public:
  static PlayerWindow *Instance();

private:
  inline static PlayerWindow *instance = nullptr;
};