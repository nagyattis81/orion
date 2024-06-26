#include "constants.hpp"
#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/geometry.hpp"
#include "engine/grid.hpp"
#include "engine/model.hpp"
#include "part.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

struct Part02 : public Part {
  vec3 clearColor = Color::LIGHTGRAY;
  vec3 eye = vec3(50, -100, 50);
  vec3 center = vec3(0, 20, 50);
  bool enableGrid = true;
  float scaleModel = 0.1f;
  vec3 translateModel = vec3(0.0f);
  Camera camera;
  Grid grid;
  Model model;

  const char *Name() override { return "Part02"; }

  bool Init() override {
    camera.Perspective(60.0f, Constants::ASPECT, 10.0f, 1000.0f);

    if (!model.Load({.fileName = "data/scenes/boat/12219_boat_v2_L2.obj",
                     .texturePath = "data/scenes/boat/"}))
      return false;

    return grid.Init({.size = 5000.0f,
                      .count = 400,
                      .normals = false,
                      .color = Color::WHITE});
  }

  void GUI() override {
    ImGui::ColorEdit3("clearColor", &clearColor.r);
    ImGui::DragFloat3("eye", &eye.x);
    ImGui::DragFloat3("center", &center.x);
    ImGui::Checkbox("enableGrid", &enableGrid);
    ImGui::DragFloat("scaleModel", &scaleModel, 0.001f, 0.001f, 1.0f, "%.3f",
                     ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragFloat3("translateModel", &translateModel.x);
  }

  void Render(const float globalTime) override {
    ClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.LookAt(eye, center, Geometry::NORMALZ);

    if (enableGrid)
      grid.Render(camera);

    mat4 m = scale(mat4(1.0f), vec3(scaleModel));

    m = rotate(m, glm::radians(sinf(globalTime) * 2.0f), vec3(1, 0, 0));
    m = rotate(m, glm::radians(cosf(globalTime) * 2.0f), vec3(0, 1, 0));
    m = translate(m,
                  vec3(cosf(globalTime) * 2.0f, 0, sinf(globalTime) * 10.0f));

    m = translate(m, translateModel);

    model.Render(camera, m);
  }
};

extern Part *CreatePart02() { return new Part02(); }
