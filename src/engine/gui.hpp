#pragma once

struct GLFWwindow;

class GUI {
private:
  inline static GUI *instance = nullptr;
  GLFWwindow *window = nullptr;
  GUI(GLFWwindow *window);

public:
  static GUI *Instance(GLFWwindow *window);

  bool Init();
  void Render();
};