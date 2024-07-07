#include "parameter.hpp"
#include "color3.hpp"
#include "constants.hpp"
#include "float.hpp"
#include "spdlog/spdlog.h"
#include "utils.hpp"
#include "vec3.hpp"
#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <jsonxx.h>

bool Parameter::LoadFromFile() {
  const string fileName = Constants::FOLDER + string(name) + ".json";
  spdlog::info("*** Load {}", fileName);
  ifstream file(fileName);
  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  if (!file.is_open())
    return true;
  jsonxx::Object object;
  if (!object.parse(str))
    return false;
  Utils::LoadFromObject(object, this);
  return true;
}

void Parameter::SaveToFile() {
  filesystem::create_directory(Constants::FOLDER);
  const string fileName = Constants::FOLDER + string(name) + ".json";
  spdlog::info("*** Save {}", fileName);
  fstream file;
  file.open(fileName, ios::out);
  if (!file.is_open()) {
    spdlog::critical("open error!");
    return;
  }
  jsonxx::Object object;
  Utils::SaveToObject(object, this);
  std::string str = object.json();
  file << str;
  file.close();
}

void Parameter::GUI() {
  switch (type) {
  case Type::TYPE_WINDOW: {
    if (show && ImGui::Begin(name.c_str(), &show)) {
      for (auto it : children)
        it->GUI();
      ImGui::End();
    }
    break;
  }
  default: {
    for (auto it : children)
      it->GUI();
  }
  }
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
