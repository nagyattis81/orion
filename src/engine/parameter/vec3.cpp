#include "vec3.hpp"
#include "src/engine/json/json.hpp"
#include <imgui.h>

void Vec3::GUI() { ImGui::DragFloat3(name.c_str(), &value->x); }

void Vec3::Load(const jsonxx::Array &array) {
  JSON::ArrayTovec3(*value, array);
}

void Vec3::Save(jsonxx::Array &array) { JSON::vec3ToArray(*value, array); }