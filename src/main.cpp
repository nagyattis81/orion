#include <argparse/argparse.hpp>

#include "engine/window/create-parameters.struct.hpp"
#include "engine/window/editor.hpp"
#include "engine/window/player.hpp"
#include <cstdlib>

const char *NAME = "orion";

bool CreateWindow(Window *window, const CreateParameters &createParameters) {
  if (!window)
    return false;
  return window->Create(&createParameters);
}

bool isEditorMode(int argc, char *argv[]) {
  argparse::ArgumentParser program(NAME);
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
  return program["--editor"] == true;
}

int main(int argc, char *argv[]) {
  Editor editor(isEditorMode(argc, argv));
  if (!CreateWindow(&editor, {.title = "editor",
                              .fullscreen = false,
                              .width = 360,
                              .height = 640,
                              .vsync = false,
                              .resize = true}))
    return EXIT_FAILURE;

  Player player;
  if (!CreateWindow(&player, *editor.GetPlayerCreateParameters(NAME)))
    return EXIT_FAILURE;

  editor.SetPlayer(&player);

  while (player.Open()) {
    player.Render();
    if (editor.Render())
      break;
  }

  editor.Delete();

  return EXIT_SUCCESS;
}