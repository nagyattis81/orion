#include "parameter.hpp"
#include "color3.hpp"
#include "constants.hpp"
#include "float.hpp"
#include "spdlog/spdlog.h"
#include "src/engine/json/json.hpp"
#include "vec3.hpp"
#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <jsonxx.h>
#include <memory>

string Parameter::GetFileName() const {
  return Constants::FOLDER + string(name) + ".json";
}

bool Parameter::LoadFromFile() {
  unique_ptr<jsonxx::Object> object(json::LoadFromFile(GetFileName()));
  if (!object)
    return false;
  LoadFromObject(*object, this);
  return true;
}

void Parameter::SaveToFile() {
  jsonxx::Object object;
  SaveToObject(object, this);
  json::SaveToFile(GetFileName(), object);
}

void Parameter::HandleChildren(Parameter *parameter, const Type filterType) {
  for (auto it : parameter->children) {
    if (filterType != Type::TYPE_COUNT && it->type == filterType)
      continue;
    it->GUI();
  }
}

void Parameter::HandleMenuItem(const char *name) {
  if (ImGui::MenuItem(name, nullptr, show))
    show = !show;
}

void Parameter::HandleWindow() {
  if (type != Type::TYPE_WINDOW)
    return;
  if (show && ImGui::Begin(name.c_str(), &show)) {
    HandleTabs();
    ImGui::End();
  }
}

void Parameter::HandleCollapse() {
  if (type != Type::TYPE_COLLAPSE)
    return;
  ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
  if (firstShow)
    flags |= ImGuiTreeNodeFlags_DefaultOpen;
  show = false;
  if (ImGui::CollapsingHeader(name.c_str(), flags)) {
    HandleTabs();
    show = true;
  }
}

void Parameter::HandleSimple() {
  if (IsGroup(type))
    return;
  HandleChildren(this);
}

void Parameter::HandleTab(Parameter *parameter) {
  ImGuiTabItemFlags tab_item_flags = ImGuiTabItemFlags_None;
  if (parameter->firstShow) {
    tab_item_flags |= ImGuiTabItemFlags_SetSelected;
    parameter->firstShow = false;
  }
  if (ImGui::BeginTabItem(parameter->name.c_str(), nullptr, tab_item_flags)) {
    parameter->show = true;
    HandleChildren(parameter);
    ImGui::EndTabItem();
  }
}

void Parameter::HandleTabs() {
  // https://medium.com/swlh/doing-it-the-functional-way-in-c-5c392bbdd46a
  const auto isNoTab =
      find_if(children.begin(), children.end(), [](Parameter *parameter) {
        return parameter->type == Type::TYPE_TAB;
      }) == children.end();
  if (isNoTab) {
    HandleChildren(this);
    return;
  }
  if (ImGui::BeginTabBar(name.c_str())) {
    for (auto it : children) {
      if (it->type != Type::TYPE_TAB)
        continue;
      it->show = false;
      HandleTab(it);
    }
    ImGui::EndTabBar();
  }
  HandleChildren(this, Type::TYPE_TAB);
}

void Parameter::GUI() {
  HandleWindow();
  HandleCollapse();
  HandleSimple();
}

void Parameter::Color3(const char *name, vec3 *color) {
  auto parameter = new ::Color3();
  parameter->type = Type::TYPE_COLOR3;
  parameter->name = name;
  parameter->value = color;
  children.push_back(parameter);
}

void Parameter::Vec3(const char *name, vec3 *value) {
  auto parameter = new ::Vec3();
  parameter->type = Type::TYPE_VEC3;
  parameter->name = name;
  parameter->value = value;
  children.push_back(parameter);
}

void Parameter::Float(const char *name, float *value, const float v_speed,
                      const float v_min, const float v_max,
                      const char *format) {
  auto parameter = new ::Float();
  parameter->type = Type::TYPE_FLOAT;
  parameter->name = name;
  parameter->value = value;
  parameter->v_speed = v_speed;
  parameter->v_min = v_min;
  parameter->v_max = v_max;
  parameter->format = format;
  children.push_back(parameter);
}

void Parameter::Group(Parameter *parameter) { children.push_back(parameter); }

void Parameter::Set(const char *name, const Type &type) {
  this->name = name;
  this->type = type;
}

bool Parameter::IsGroup(const Type type) {
  return type == Type::TYPE_WINDOW || type == Type::TYPE_COLLAPSE ||
         type == Type::TYPE_TAB;
}

void Parameter::SaveToObject(jsonxx::Object &object, Parameter *parameter) {
  jsonxx::Object data;
  data << "type" << Constants::TYPE_NAMES[parameter->type];

  if (IsGroup(parameter->type)) {
    data << "show" << parameter->show;
  } else {
    jsonxx::Array arr;
    parameter->Save(arr);
    data << "value" << arr;
  }

  if (!parameter->children.empty()) {
    jsonxx::Object children;
    for (auto it : parameter->children)
      SaveToObject(children, it);
    data << "children" << children;
  }
  object << parameter->name << data;
}

void Parameter::LoadFromObject(const jsonxx::Object &object,
                               Parameter *parameter) {
  if (!object.has<jsonxx::Object>(parameter->name))
    return;
  const auto data = object.get<jsonxx::Object>(parameter->name);

  if (!data.has<jsonxx::String>("type"))
    return;

  const string typeStr = data.get<jsonxx::String>("type");
  Type type = Type::TYPE_COUNT;
  for (unsigned int i = 0; i < Type::TYPE_COUNT; i++) {
    if (typeStr == Constants::TYPE_NAMES[i]) {
      type = Type(i);
      break;
    }
  }
  if (type == Type::TYPE_COUNT || parameter->type != type)
    return;

  if (data.has<jsonxx::Boolean>("show")) {
    parameter->show = data.get<jsonxx::Boolean>("show");
    parameter->firstShow = parameter->show;
  }

  if (data.has<jsonxx::Array>("value"))
    parameter->Load(data.get<jsonxx::Array>("value"));

  if (!data.has<jsonxx::Object>("children"))
    return;
  const auto children = data.get<jsonxx::Object>("children");

  for (auto it : parameter->children) {
    LoadFromObject(children, it);
  }
}
