#include "float.hpp"
#include "src/engine/json/json.hpp"
#include <imgui.h>

void Float::GUI() {
  ImGui::DragFloat(name.c_str(), value, v_speed, v_min, v_max, format,
                   ImGuiSliderFlags_AlwaysClamp);
}

void Float::Load(const jsonxx::Array &array) {
  json::LoadFloatFromfloat(*value, array);
}

void Float::Save(jsonxx::Array &array) {
  json::SaveFloatToArray(*value, array);
}