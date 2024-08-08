#include "src/engine/window/editor.hpp"
#include <imgui.h>

extern void Settings(bool *show) {
  if (*show && ImGui::Begin("Settings", show)) {
    ImGuiIO &io = ImGui::GetIO();
    if (ImGui::SliderFloat("Scale", &io.FontGlobalScale, 1.0f, 3.0f)) {
      Editor::Instance()->settings.scale = io.FontGlobalScale;
    }
    ImGui::End();
  }
}