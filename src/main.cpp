#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "engine/gui.hpp"
#include "engine/music.hpp"
#include "engine/window.hpp"
#include <memory>

using namespace std;

int main() {

  unique_ptr<Window> window(Window::Instance());
  if (!window->Create(
          {.title = "demo", .fullscreen = false, .vsync = false, .samples = 4}))
    return EXIT_FAILURE;

  unique_ptr<Demo> demo(Demo::Instance());
  spdlog::info("!!! Demo init");
  if (!demo->Init())
    return EXIT_FAILURE;

  unique_ptr<GUI> gui(GUI::Instance());
  if (!gui->Init(window->GetHandle()))
    return EXIT_FAILURE;

  unique_ptr<Music> music(Music::Instance());
  if (!music->Load({.path = Demo::MUSIC, .volume = Demo::MUTE ? 0.0f : 1.0f}))
    return EXIT_FAILURE;

  music->SetTime(Demo::OFFSET);
  music->Play();

  while (window->Open()) {
    window->PollEvents();

    gui->Frame();

    const double time = music->GetTime();
    demo->Begin(time);
    demo->Render(time);
    demo->End(time);

    gui->Render();

    window->SwapBuffers();
  }

  if (Demo::EDITOR)
    demo->Delete();

  return EXIT_SUCCESS;
}