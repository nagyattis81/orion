#pragma once

struct GLFWwindow;

class GUI {
  // TODO instance class
public:
  bool Init(GLFWwindow *window);
  void Frame();
  void Render();
};