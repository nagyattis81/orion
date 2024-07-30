#include "engine/window/editor.hpp"
#include "engine/window/player.hpp"
#include <cstdlib>

int main() {

  Editor editor(true);

  if (!editor.Create({.title = "editor",
                      .fullscreen = false,
                      .width = 360,
                      .height = 640,
                      .vsync = false}))
    return EXIT_FAILURE;

  Player player;
  if (!player.Create({.title = "demo",
                      .fullscreen = false,
                      .width = 1280,
                      .height = 720,
                      .vsync = true,
                      .samples = 4}))
    return EXIT_FAILURE;

  while (player.Open()) {
    player.Render();
    if (editor.Render())
      break;
  }

  return EXIT_SUCCESS;
}