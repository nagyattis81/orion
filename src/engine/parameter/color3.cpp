#include "color3.hpp"
#include "src/engine/json/json.hpp"
#include <imgui.h>

void Color3::GUI() { ImGui::ColorEdit3(name.c_str(), &value->r); }

void Color3::Load(const jsonxx::Array &array) {
  json::LoadArrayFromVec3(*value, array);
}

void Color3::Save(jsonxx::Array &array) {
  json::SaveVec3ToArray(*value, array);
}