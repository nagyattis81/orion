#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

using namespace glm;

class Music;
class Demo;

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

class Window {
public:
  ~Window();

  bool Create(const CreateParameters &createParameters);

  virtual bool Init() = 0;
  virtual void Start() = 0;

  bool Open() const;
  void SwapBuffers() const;
  void PollEvents() const;
  double GetTime() const;
  void SetWindowTitle(const char *title);
  void Render();

  void MakeContextCurrent() const;

  ivec2 GetPosition() const;
  ivec2 GetSize() const;

protected:
  GLFWwindow *window = nullptr;
  Music *music = nullptr;
  Demo *demo = nullptr;
  // TODO FBO
};
