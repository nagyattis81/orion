#include "vec3.hpp"
#include <imgui.h>

void Vec3::GUI() { ImGui::DragFloat3(name.c_str(), &value->x); }

void Vec3::Load(const jsonxx::Array &arr) {
  value->x = static_cast<float>(arr.get<jsonxx::Number>(0));
  value->y = static_cast<float>(arr.get<jsonxx::Number>(1));
  value->z = static_cast<float>(arr.get<jsonxx::Number>(2));
}

void Vec3::Save(jsonxx::Array &arr) {
  arr << value->x;
  arr << value->y;
  arr << value->z;
}