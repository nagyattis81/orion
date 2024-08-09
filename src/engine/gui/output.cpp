#include "src/engine/window/editor.hpp"
#include <imgui.h>

static void AspectRatio(ImGuiSizeCallbackData *data) {
  float aspect_ratio = *(float *)data->UserData;
  data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio);
}

extern void Output() {
  static bool showInfo = false;
  static ImVec2 size;

  static const float aspect_ratio = 16.0f / 9.0f;
  ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX),
                                      AspectRatio, (void *)&aspect_ratio);

  if (ImGui::Begin("Output", nullptr,
                   ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar)) {
    if (ImGui::BeginMenuBar()) {
      if (ImGui::MenuItem("Info", nullptr, showInfo))
        showInfo = !showInfo;

      if (ImGui::BeginMenu("Size")) {
        ImGui::MenuItem("  90p");
        ImGui::MenuItem(" 180p");
        ImGui::MenuItem(" 360p");
        ImGui::MenuItem(" 720p");
        ImGui::MenuItem("1080p");
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Viewport")) {
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    auto &fbo = Editor::Instance()->fbo;
    const auto y = ImGui::GetContentRegionAvail().y;
    const float x = y * aspect_ratio;

    size.x = x;
    size.y = y;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() +
                         (ImGui::GetContentRegionAvail().x - x) * 0.5f);
    fbo.GetColor().ImGuiImage(x, y);
    ImGui::End();
  }

  if (showInfo &&
      ImGui::Begin("Info", &showInfo, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("size = %f x %f", size.x, size.y);
    ImGui::End();
  }
}