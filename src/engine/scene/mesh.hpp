#pragma once

#include "material/material.hpp"
#include "src/engine/gl/buffers.hpp"
#include "src/engine/gl/vao.hpp"

struct Mesh {
  Material *material = nullptr;
  VAO vao;
  VBO vbo;

  bool Init(const aiMesh *mesh);
  void Render(const bool transparent, const Camera &camera,
              const mat4 &modelMatrix) const;
};
