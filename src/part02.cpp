#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/geometry.hpp"
#include "engine/grid.hpp"
#include "engine/model.hpp"
#include "engine/part.hpp"
#include "engine/scene/scene.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

struct Part02 : public Part {
  vec3 clearColor = Color::LIGHTGRAY;
  float scaleModel = 0.1f;
  vec3 translateModel = vec3(0.0f);

  Camera camera;
  Grid grid;
  Model model;
  Scene scene;

  Part02(const char *name, const bool showWindow) : Part(name, showWindow) {
    parameters.Color3("clearColor", &clearColor);
    parameters.Float("scaleModel", &scaleModel, 0.001f, 0.001f, 1.0f, "%.3f");
    parameters.Vec3("translateModel", &translateModel);
    parameters.Children({
        camera.GetParameters(),
        grid.GetParameters(),
        scene.GetParameters(),
    });
  }

  bool Init() override {
    if (!model.Load("data/scenes/boat/12219_boat_v2_L2.obj"))
      return false;

    if (!scene.Init(model.scene, "data/scenes/boat/"))
      return false;

    return grid.Init({.size = 5000.0f,
                      .count = 400,
                      .normals = false,
                      .color = Color::WHITE});
  }

  void Render(const float globalTime) override {
    ClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Perspective();
    camera.LookAt();
    grid.Render(camera);

    mat4 m = scale(mat4(1.0f), vec3(scaleModel));
    m = rotate(m, glm::radians(sinf(globalTime) * 2.0f), vec3(1, 0, 0));
    m = rotate(m, glm::radians(cosf(globalTime) * 2.0f), vec3(0, 1, 0));
    m = translate(m,
                  vec3(cosf(globalTime) * 2.0f, 0, sinf(globalTime) * 10.0f));
    m = translate(m, translateModel);

    scene.Render(camera, m);
  }
};

extern Part *CreatePart02(const bool showWindow) {
  return new Part02("Part02", showWindow);
}
