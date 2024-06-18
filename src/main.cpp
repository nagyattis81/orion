#include "spdlog/spdlog.h"

#include "constants.hpp"
#include "demo.hpp"
#include "engine/music.hpp"
#include "engine/window.hpp"
#include "part.hpp"
#include <memory>

using namespace std;

int main() {

  unique_ptr<Window> window(Window::Instance());
  if (!window->Create(
          {.title = "demo", .fullscreen = false, .vsync = false, .samples = 4}))
    return EXIT_FAILURE;

  Demo demo;
  spdlog::info("!!! Demo init");
  if (!demo.Init())
    return EXIT_FAILURE;

  map<double, Part *> parts = demo.CreateParts();

  double start = 0;
  for (auto it : parts) {
    spdlog::info("*** Part {} init", it.first);
    if (!it.second->Init())
      return EXIT_FAILURE;
    it.second->start = start;
    it.second->end = it.first;
    start = it.first;
    it.second->demo = &demo;
  }

  unique_ptr<Music> music(Music::Instance());
  if (!music->Load(
          {.path = Constants::MUSIC, .volume = Constants::MUTE ? 0.0f : 1.0f}))
    return EXIT_FAILURE;
  music->SetTime(Constants::OFFSET);
  music->Play();

  while (window->Open()) {
    const double time = music->GetTime();

    if (Constants::TITLE_TIME) {
      static char buffer[64];
      snprintf(buffer, 64, "%f", time);
      window->SetWindowTitle(buffer);
    }

    for (auto it : parts)
      if (it.second->start <= time && time < it.second->end)
        it.second->Render(static_cast<float>(time));
    demo.Render(time);

    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}