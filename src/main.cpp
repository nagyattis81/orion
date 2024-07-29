#include "engine/window/editor.hpp"
#include "engine/window/player.hpp"
#include <cstdlib>

int main() {
  Editor editor;
  if (!editor.Create({.title = "editor",
                      .fullscreen = false,
                      .width = 1920,
                      .height = 1080,
                      .vsync = false}))
    return EXIT_FAILURE;

  Player player;
  if (!player.Create({.title = "demo",
                      .fullscreen = false,
                      .width = 1920,
                      .height = 1080,
                      .vsync = true,
                      .samples = 4}))
    return EXIT_FAILURE;

  while (player.Open() && editor.Open()) {
    player.Render();
    editor.Render();
  }

  editor.Delete();

  return EXIT_SUCCESS;
}