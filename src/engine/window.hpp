#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
  static Window *Instance();

  ~Window();
  struct CretaParameters {
    const char *title = nullptr;
    bool fullscreen = false;
    bool vsync = true;
    unsigned char samples = 0;
    GLFWkeyfun keyCallback = nullptr;
  };

  bool Create(const CretaParameters &cretaParameters);

  bool Open() const;
  void SwapBuffers() const;
  void PollEvents() const;
  double GetTime() const;
  void SetWindowTitle(const char *title);
  GLFWwindow *GetHandle() const;

private:
  inline static Window *instance = nullptr;
  GLFWwindow *window = nullptr;
};
