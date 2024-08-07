#include "spdlog/spdlog.h"

#include "../../demo.hpp"

#include "../../engine/json.hpp"
#include "../../engine/music.hpp"
#include "../gui.hpp"
#include "editor.hpp"
#include "player.hpp"
#include <fstream>
#include <jsonxx.h>
#include <memory>

using namespace std;

auto FILE_NAME = "data/editor.json";

Editor::Editor() {}

bool Editor::Init() {
  if (!Load())
    return false;

  if (!Create({
          .title = "editor",
          .fullscreen = false,
          .width = 1280,
          .height = 720,
          .vsync = true,
          .resize = true,
      }))
    return false;

  gui = GUI::Instance(window);

  return gui && gui->Init(1.0f);
}

void Editor::Start() {
  while (Open()) {
    Render();
    PollEvents();
    gui->Render();
    SwapBuffers();
  }
  demo->Delete();
  Save();
}

bool Editor::Load() {
  unique_ptr<jsonxx::Object> object(JSON::Load(FILE_NAME));
  if (!object)
    return true;

  return true;
}

void Editor::Save() {

  jsonxx::Object object;
  JSON::Save(FILE_NAME, object);
}