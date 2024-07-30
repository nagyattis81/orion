#include <argparse/argparse.hpp>

#include "engine/window/editor.hpp"
#include "engine/window/player.hpp"
#include <cstdlib>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("orion");

  program.add_argument("--editor")
      .help("editor mode")
      .default_value(false)
      .implicit_value(true);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  Editor editor(program["--editor"] == true);

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