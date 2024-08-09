#include "spdlog/spdlog.h"
#include <glad/glad.h>

#include "editor.hpp"
#include "src/demo.hpp"
#include "src/engine//music.hpp"
#include "src/engine/constants/color.hpp"
#include "src/engine/gui/gui.hpp"
#include "src/engine/json/json.hpp"
#include <jsonxx.h>
#include <memory>

using namespace std;

static auto FILE_NAME = "data/editor.json";

Editor *Editor::Instance() {
  if (!instance)
    instance = new Editor();
  return instance;
}

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

void Editor::Render() {
  static const auto &color = constants::Color::EDITOR_BACKGROUND;
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  fbo.Bind();
  Window::Render();
  fbo.UnBind();
}

bool Editor::Load() {
  unique_ptr<jsonxx::Object> object(json::LoadFromFile(FILE_NAME));
  if (!object)
    return true;
  json::LoadObject(*object, "settings", settings);
  return true;
}

void Editor::Save() {
  jsonxx::Object object;
  json::SaveObject(object, "settings", settings);
  json::SaveToFile(FILE_NAME, object);
}