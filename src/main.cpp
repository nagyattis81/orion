#include <glad/glad.h>

#include "music.hpp"
#include "window.hpp"
#include <cstdlib>
#include <memory>

int main() {

  std::unique_ptr<Window> window(Window::Instance());

  if (!window->Create("demo", 1280, 720, Window::Fullscreen::ON,
                      Window::Vsync::OFF))
    return EXIT_FAILURE;

  std::unique_ptr<Music> music(Music::Instance());
  if (!music->Load("data/music.mp3"))
    return EXIT_FAILURE;

  music->Play();
  while (window->Open()) {
    const float time = static_cast<float>(music->GetTime()) * 8.0f;
    const float value = sinf(time) * 0.5f + 0.5f;
    glClearColor(value, value, value, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}