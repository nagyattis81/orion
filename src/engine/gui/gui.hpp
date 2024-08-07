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

  float scale = 1.0f;

  GUI(GLFWwindow *window);

  void Menu();
  void Windows();
  void Load();

public:
  static GUI *Instance(GLFWwindow *window);

  bool Init();
  void Render();
  void Save();
};