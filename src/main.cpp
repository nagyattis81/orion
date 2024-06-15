#include "demo.hpp"
#include "engine/music.hpp"
#include "engine/window.hpp"
#include <memory>

int main() {

  std::unique_ptr<Window> window(Window::Instance());
  if (!window->Create({.title = "demo", .fullscreen = false, .vsync = false}))
    return EXIT_FAILURE;

  Demo demo;
  if (!demo.Init())
    return EXIT_FAILURE;

  std::unique_ptr<Music> music(Music::Instance());
  if (!music->Load({.path = "data/music.mp3", .volume = 0.0f}))
    return EXIT_FAILURE;
  music->Play();

  while (window->Open()) {

    if (demo.Render(music->GetTime()))
      break;

    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}