#pragma once

#include <GLFW/glfw3.h>

struct CreateParameters {
  const char *title = nullptr;
  bool fullscreen = false;
  int x = -1;
  int y = -1;
  int width = -1;
  int height = -1;
  bool vsync = true;
  unsigned char samples = 0;
  GLFWkeyfun keyCallback = nullptr;
  bool resize = false;
};