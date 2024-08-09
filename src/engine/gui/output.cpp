#include "src/engine/window/editor.hpp"
#include <imgui.h>

static void AspectRatio(ImGuiSizeCallbackData *data) {
  float aspect_ratio = *(float *)data->UserData;
  data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio);
}

extern void Output() {
  float aspect_ratio = 16.0f / 9.0f;
  ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX),
                                      AspectRatio, (void *)&aspect_ratio);
  if (ImGui::Begin("Output")) {
    auto &fbo = Editor::Instance()->fbo;
    ImGui::Image((void *)(intptr_t)fbo.color, ImGui::GetContentRegionAvail(),
                 ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
  }
}