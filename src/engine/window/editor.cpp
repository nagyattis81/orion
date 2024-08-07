#include "spdlog/spdlog.h"

#include "../../demo.hpp"

#include "../../engine/json.hpp"
#include "../../engine/music.hpp"
#include "../gui.hpp"
#include "create-parameters.struct.hpp"
#include "editor.hpp"
#include "player.hpp"
#include <fstream>
#include <jsonxx.h>
#include <memory>

using namespace std;

auto FILE_NAME = "data/editor.json";

Editor::Editor(const bool enable)
    : disable(!enable), playerCreateParameters(new CreateParameters({
                            .title = "player",
                            .fullscreen = false,
                            .width = 1280,
                            .height = 720,
                            .vsync = true,
                            .samples = 4,
                        })) {}

void Editor::SetPlayer(Player *player) { this->player = player; }

bool Editor::Create(const CreateParameters *createParameters) {
  if (disable)
    return true;

  CreateParameters newCreateParameters = *createParameters;
  if (!Load(newCreateParameters))
    return false;

  if (!Window::Create(&newCreateParameters))
    return false;
  gui = GUI::Instance(GetHandle());
  return gui && gui->Init();
}

bool Editor::Render() {
  if (disable)
    return false;

  MakeContextCurrent();
  glClear(GL_COLOR_BUFFER_BIT);

  PollEvents();
  gui->Render();
  SwapBuffers();

  return !Open();
}

void Editor::Delete() {
  if (disable)
    return;
  Demo::Instance()->Delete();
  Save();
}

CreateParameters *Editor::GetPlayerCreateParameters(const char *title) {
  playerCreateParameters->title = title;
  return playerCreateParameters;
}

void WindowToObject(Window *window, const string &name,
                    jsonxx::Object &targetObject) {
  jsonxx::Object object;
  JSON::ivec2ToObject(window->GetPosition(), "position", object);
  JSON::ivec2ToObject(window->GetSize(), "size", object);
  targetObject << name << object;
}

void ObjectToCreateParameters(const jsonxx::Object &sourceObject,
                              const string &name,
                              CreateParameters &createParameters) {
  ivec2 position;
  JSON::ObjectToivec2(position, "position", sourceObject);
  createParameters.x = position.x;
  createParameters.y = position.y;

  ivec2 size;
  JSON::ObjectToivec2(size, "size", sourceObject);
  createParameters.width = size.x;
  createParameters.height = size.y;
}

bool Editor::Load(CreateParameters &createParameters) {
  unique_ptr<jsonxx::Object> object(JSON::Load(FILE_NAME));
  if (!object)
    return true;

  if (!object->has<jsonxx::Object>("window"))
    return false;

  const auto windowObject = object->get<jsonxx::Object>("window");
  if (windowObject.has<jsonxx::Object>("editor"))
    ObjectToCreateParameters(windowObject.get<jsonxx::Object>("editor"),
                             "editor", createParameters);
  if (windowObject.has<jsonxx::Object>("player"))
    ObjectToCreateParameters(windowObject.get<jsonxx::Object>("player"),
                             "player", *playerCreateParameters);
  return true;
}

void Editor::Save() {

  jsonxx::Object saveObject;
  jsonxx::Object windowObject;
  WindowToObject(this, "editor", windowObject);
  WindowToObject(player, "player", windowObject);
  saveObject << "window" << windowObject;
  JSON::Save(FILE_NAME, saveObject);
}