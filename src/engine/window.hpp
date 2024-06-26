#pragma once

struct GLFWwindow;

class Window {
public:
  static Window *Instance();

  ~Window();
  struct Parameters {
    const char *title = nullptr;
    bool fullscreen = false;
    bool vsync = true;
    unsigned char samples = 0;
  };

  bool Create(const Parameters &parameters);

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
