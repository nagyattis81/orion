#pragma once

struct GLFWwindow;

class Window {
public:
  enum class Fullscreen { ON, OFF };
  enum class Vsync { ON, OFF };

  static Window *Instance();

  ~Window();
  bool Create(const char *title, unsigned int width, unsigned int height,
              const Fullscreen fullscreen, const Vsync vsync);

  bool Open() const;
  void SwapBuffers() const;
  void PollEvents() const;

private:
  inline static Window *instance = nullptr;
  GLFWwindow *window = nullptr;
};
