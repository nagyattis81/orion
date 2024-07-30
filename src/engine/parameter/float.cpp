#include "float.hpp"
#include "../json.hpp"
#include <imgui.h>

void Float::GUI() {
  ImGui::DragFloat(name.c_str(), value, v_speed, v_min, v_max, format,
                   ImGuiSliderFlags_AlwaysClamp);
}

void Float::Load(const jsonxx::Array &array) {
  JSON::ArrayTofloat(*value, array);
}

void Float::Save(jsonxx::Array &array) { JSON::floatToArray(*value, array); }