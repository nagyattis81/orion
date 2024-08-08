#include "src/engine/window/editor.hpp"
#include <imgui.h>

extern void Output() {
  if (ImGui::Begin("Output")) {
    auto &fbo = Editor::Instance()->fbo;
    const auto x = ImGui::GetContentRegionAvail().x;
    const float y = x * (9.0f / 16.0f);
    ImGui::Image(ImTextureID(fbo.color.id), ImVec2(x, y), ImVec2(0, 1),
                 ImVec2(1, 0));
    ImGui::End();
  }
}