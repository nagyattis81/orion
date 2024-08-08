#pragma once

struct GLFWwindow;

class GUI {
private:
  inline static GUI *instance = nullptr;
  GLFWwindow *window = nullptr;

  struct {
    bool demoWindow = false;
    bool settings = false;
  } show;

  GUI(GLFWwindow *window);

  void Menu();
  void Windows();

public:
  static GUI *Instance(GLFWwindow *window);

  bool Init(const float scale);
  void Render();
};