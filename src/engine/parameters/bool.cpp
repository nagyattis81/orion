#include "bool.hpp"
#include <imgui.h>

void Bool::GUI() { ImGui::Checkbox(name, value); }

void Bool::Save(jsonxx::Array &array) { array << *value; }

bool Bool::Load(const jsonxx::Array &array) {
  if (array.size() != 1)
    return false;
  *value = array.get<jsonxx::Boolean>(0);
  return true;
}
