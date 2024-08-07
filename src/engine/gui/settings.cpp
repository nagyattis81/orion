#include <imgui.h>

extern void Settings(bool *show) {
  if (*show && ImGui::Begin("Settings", show)) {
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SliderFloat("Scale", &io.FontGlobalScale, 1.0f, 3.0f);
    ImGui::End();
  }
}