#pragma once

#include "buffers.hpp"
#include "color.hpp"
#include "program.hpp"
#include "vao.hpp"
#include <glm/mat4x4.hpp>

using namespace glm;

class Camera;

class Grid {
private:
  Program program;
  VAO vao;
  VBO vbo;
  GLint mvpLocation = -1;

public:
  struct Parameters {
    float size = 10.0f;
    unsigned int count = 10;
    bool normals = false;
    unsigned int thickening = 5;
    const vec3 color = Color::GREEN;
  };
  bool Init(const Parameters &parameters);
  void Render(const Camera &camera, const mat4 &modelMatrix = mat4(1.0f));
};