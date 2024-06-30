#include "vec3.hpp"
#include <imgui.h>

void Vec3::GUI() { ImGui::DragFloat3(name, &value->x); }

void Vec3::Save(jsonxx::Array &array) {
  array << value->x;
  array << value->y;
  array << value->z;
}

bool Vec3::Load(const jsonxx::Array &array) {
  if (array.size() != 3)
    return false;
  value->x = static_cast<float>(array.get<jsonxx::Number>(0));
  value->y = static_cast<float>(array.get<jsonxx::Number>(1));
  value->z = static_cast<float>(array.get<jsonxx::Number>(2));
  return true;
}
