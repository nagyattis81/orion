#include "window.hpp"
#include <cstdlib>
#include <memory>

int main() {

  std::unique_ptr<Window> window(Window::Instance());

  if (!window->Create("demo", 1280, 720, Window::Fullscreen::OFF,
                      Window::Vsync::OFF))
    return EXIT_FAILURE;

  while (window->Open()) {
    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}