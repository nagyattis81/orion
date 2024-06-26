#pragma once

struct GLFWwindow;

class GUI {
private:
  inline static GUI *instance = nullptr;

  bool disable = true;
  bool show = true;

  GUI(const bool disable) : disable(disable) {}

public:
  static GUI *Instance();
  bool Init(GLFWwindow *window);
  void Frame();
  void Render();
};