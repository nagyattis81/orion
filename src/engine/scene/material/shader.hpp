#pragma once

#include "material.hpp"
#include "src/engine/gl/program.hpp"

struct Material::Shader {
  Program program;
  GLint mvpLocation = -1;
  GLint normalMatrixLocation = -1;
  GLint modelViewMatrixLocation = -1;

  bool Load();
  void Bind(const Camera &camera, const mat4 &modelMatrix);
  void UnBind();
};
