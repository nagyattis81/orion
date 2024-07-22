#include "color3.hpp"
#include <imgui.h>

void Color3::GUI() { ImGui::ColorEdit3(name.c_str(), &value->r); }

void Color3::Load(const jsonxx::Array &arr) {
  value->r = static_cast<float>(arr.get<jsonxx::Number>(0));
  value->g = static_cast<float>(arr.get<jsonxx::Number>(1));
  value->b = static_cast<float>(arr.get<jsonxx::Number>(2));
}

void Color3::Save(jsonxx::Array &arr) {
  arr << value->r;
  arr << value->g;
  arr << value->b;
}