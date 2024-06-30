
#include "parameter.hpp"
#include "parameters.hpp"
#include <imgui.h>

void Parameters::GUI() {
  for (auto it : items)
    it->GUI();
  for (auto it : children) {
    if (!it)
      continue;
    if (ImGui::CollapsingHeader(it->type.c_str())) {
      if (it->name != "")
        ImGui::SeparatorText(it->name.c_str());
      it->GUI();
    }
  }
}
