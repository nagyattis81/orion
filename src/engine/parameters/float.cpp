#include "float.hpp"
#include <imgui.h>

void Float::GUI() {
  ImGui::DragFloat(name, value, v_speed, v_min, v_max, format,
                   ImGuiSliderFlags_AlwaysClamp);
}

void Float::Save(jsonxx::Array &array) { array << *value; }

bool Float::Load(const jsonxx::Array &array) {
  if (array.size() != 1)
    return false;
  *value = static_cast<float>(array.get<jsonxx::Number>(0));
  return true;
}
