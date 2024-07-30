#include "color3.hpp"
#include "../json.hpp"
#include <imgui.h>

void Color3::GUI() { ImGui::ColorEdit3(name.c_str(), &value->r); }

void Color3::Load(const jsonxx::Array &array) {
  JSON::ArrayTovec3(*value, array);
}

void Color3::Save(jsonxx::Array &array) { JSON::vec3ToArray(*value, array); }