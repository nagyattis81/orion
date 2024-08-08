#include "engine/window/editor.hpp"
#include "engine/window/player.hpp"
#include <argparse/argparse.hpp>
#include <cstdlib>

bool isEditorMode(int argc, char *argv[]) {
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
  return program["--editor"] == true;
}

int main(int argc, char *argv[]) {
  Window *window = nullptr;
  if (isEditorMode(argc, argv))
    window = Editor::Instance();
  else
    window = Player::Instance();
  if (!window || !window->Init())
    return EXIT_FAILURE;
  window->Start();
  return EXIT_SUCCESS;
}