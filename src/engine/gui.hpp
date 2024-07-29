#pragma once

struct GLFWwindow;

class GUI {
public:
  bool Init(GLFWwindow *window);
  void Frame();
  void Render();
};