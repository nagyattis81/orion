#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
  ~Window();
  struct CretaParameters {
    const char *title = nullptr;
    bool fullscreen = false;
    int width = -1;
    int height = -1;
    bool vsync = true;
    unsigned char samples = 0;
    GLFWkeyfun keyCallback = nullptr;
  };

  virtual bool Create(const CretaParameters &cretaParameters);
  virtual void Render() = 0;

  bool Open() const;
  void SwapBuffers() const;
  void PollEvents() const;
  double GetTime() const;
  void SetWindowTitle(const char *title);
  GLFWwindow *GetHandle() const;

  void MakeContextCurrent() const;
  ;

private:
  GLFWwindow *window = nullptr;
};
