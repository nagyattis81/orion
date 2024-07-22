#include "float.hpp"
#include <imgui.h>

void Float::GUI() {
  ImGui::DragFloat(name.c_str(), value, v_speed, v_min, v_max, format,
                   ImGuiSliderFlags_AlwaysClamp);
}

void Float::Load(const jsonxx::Array &arr) {
  *value = static_cast<float>(arr.get<jsonxx::Number>(0));
}

void Float::Save(jsonxx::Array &arr) { arr << *value; }