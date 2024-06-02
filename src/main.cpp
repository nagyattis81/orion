#include <glad/glad.h>

#include "window.hpp"
#include <cstdlib>
#include <memory>

int main() {

  std::unique_ptr<Window> window(Window::Instance());

  if (!window->Create("demo", 1280, 720, Window::Fullscreen::OFF,
                      Window::Vsync::OFF))
    return EXIT_FAILURE;

  while (window->Open()) {
    const float time = static_cast<float>(window->GetTime()) * 8.0f;
    const float value = sinf(time) * 0.5f + 0.5f;
    glClearColor(value, value, value, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}