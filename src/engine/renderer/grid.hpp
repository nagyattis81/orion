#pragma once

#include "src/engine/constants/color.hpp"
#include "src/engine/gl/buffers.hpp"
#include "src/engine/gl/program.hpp"
#include "src/engine/gl/vao.hpp"
#include "src/engine/parameter/parameter.hpp"
#include <glm/mat4x4.hpp>

using namespace glm;

struct Camera;

class Grid {
private:
  gl::Program program;
  gl::VAO vao;
  gl::VBO vbo;
  GLint mvpLocation = -1;
  bool enable = true;
  Parameter parameter;

public:
  Grid();
  struct InitParameters {
    float size = 10.0f;
    unsigned int count = 10;
    bool normals = false;
    unsigned int thickening = 5;
    const vec3 color = constants::Color::GREEN;
  };
  bool Init(const InitParameters &initParameters);
  void Render(const Camera &camera, const mat4 &modelMatrix = mat4(1.0f));
};