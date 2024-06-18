#include "constants.hpp"
#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/geometry.hpp"
#include "engine/grid.hpp"
#include "engine/model.hpp"
#include "part.hpp"
#include <glm/gtc/matrix_transform.hpp>

struct Part02 : public Part {
  Camera camera;
  Grid grid;
  Model model;

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

  void Render(const float globalTime) override {
    ClearColor(Color::LIGHTGRAY);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.LookAt(vec3(50, -100, 50), vec3(0, 20, 50), Geometry::NORMALZ);
    grid.Render(camera);
    mat4 m = scale(mat4(1.0f), vec3(0.1f));
    m = rotate(m, glm::radians(sinf(globalTime) * 2.0f), vec3(1, 0, 0));
    m = rotate(m, glm::radians(cosf(globalTime) * 2.0f), vec3(0, 1, 0));
    m = translate(m,
                  vec3(cosf(globalTime) * 2.0f, 0, sinf(globalTime) * 10.0f));
    model.Render(camera, m);
  }
};

extern Part *CreatePart02() { return new Part02(); }
