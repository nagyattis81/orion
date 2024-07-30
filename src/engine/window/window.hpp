#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

using namespace glm;

struct CreateParameters;

class Window {
public:
  ~Window();

  virtual bool Create(const CreateParameters *createParameters);

  bool Open() const;
  void SwapBuffers() const;
  void PollEvents() const;
  double GetTime() const;
  void SetWindowTitle(const char *title);
  GLFWwindow *GetHandle() const;

  void MakeContextCurrent() const;

  ivec2 GetPosition() const;
  ivec2 GetSize() const;

private:
  GLFWwindow *window = nullptr;
};
