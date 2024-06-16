#include "constants.hpp"
#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/geometry.hpp"
#include "engine/grid.hpp"
#include "part.hpp"
#include <glm/gtc/matrix_transform.hpp>

struct Part02 : public Part {
  Camera camera;
  Grid grid;

  bool Init() override {
    camera.Perspective(60.0f, Constants::ASPECT, 0.1f, 100.0f);
    return grid.Init({.size = 100.0f, .count = 400, .normals = true});
  }

  void Render(const float globalTime) override {
    ClearColor(Color::BLACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const float value = (sinf(globalTime) * 0.5f + 0.5f) * 0.9f;
    camera.LookAt(vec3(2.0f, 2.0f, 2.0f * value + 0.2f), Geometry::ORIGO,
                  Geometry::NORMALZ);
    grid.Render(camera,
                rotate(mat4(1.0f), globalTime * 0.25f, Geometry::NORMALZ));
  }
};

extern Part *CreatePart02() { return new Part02(); }
