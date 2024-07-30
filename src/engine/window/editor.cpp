#include "spdlog/spdlog.h"

#include "../../demo.hpp"

#include "../../engine/json.hpp"
#include "../../engine/music.hpp"
#include "create-parameters.struct.hpp"
#include "editor.hpp"
#include "player.hpp"
#include <fstream>
#include <jsonxx.h>

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
  return gui.Init(GetHandle());
}

bool Editor::Render() {
  if (disable)
    return false;

  MakeContextCurrent();
  glClear(GL_COLOR_BUFFER_BIT);

  PollEvents();
  gui.Frame();
  gui.Render();
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
  spdlog::info("*** Load {}", FILE_NAME);
  ifstream file(FILE_NAME);
  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  if (!file.is_open())
    return false;

  jsonxx::Object loadObject;
  if (!loadObject.parse(str))
    return false;

  if (!loadObject.has<jsonxx::Object>("window"))
    return false;
  const auto windowObject = loadObject.get<jsonxx::Object>("window");
  if (windowObject.has<jsonxx::Object>("editor"))
    ObjectToCreateParameters(windowObject.get<jsonxx::Object>("editor"),
                             "editor", createParameters);
  if (windowObject.has<jsonxx::Object>("player"))
    ObjectToCreateParameters(windowObject.get<jsonxx::Object>("player"),
                             "player", *playerCreateParameters);
  return true;
}

void Editor::Save() {
  spdlog::info("*** Save {}", FILE_NAME);
  fstream file;
  file.open(FILE_NAME, ios::out);
  if (!file.is_open()) {
    spdlog::critical("open error!");
    return;
  }

  jsonxx::Object saveObject;
  jsonxx::Object windowObject;
  WindowToObject(this, "editor", windowObject);
  WindowToObject(player, "player", windowObject);
  saveObject << "window" << windowObject;
  std::string str = saveObject.json();

  file << str;
  file.close();
}