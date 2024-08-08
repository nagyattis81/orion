#include "spdlog/spdlog.h"
#include <glad/glad.h>

#include "editor.hpp"
#include "src/demo.hpp"
#include "src/engine//music.hpp"
#include "src/engine/gui/gui.hpp"
#include "src/engine/json/json.hpp"
#include <jsonxx.h>
#include <memory>

using namespace std;

static auto FILE_NAME = "data/editor.json";

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

  return gui && gui->Init(settings.scale);
}

void Editor::Start() {
  while (Open()) {
    Render();
    PollEvents();
    gui->Render();
    SwapBuffers();
  }
  demo->Save();
  Save();
}

bool Editor::Load() {
  unique_ptr<jsonxx::Object> object(json::LoadFromFile(FILE_NAME));
  if (!object)
    return true;
  return true;
}

void Editor::Save() {
  jsonxx::Object object;
  json::SaveToFile(FILE_NAME, object);
}