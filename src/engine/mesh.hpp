#pragma once

#include "buffers.hpp"
#include "material/material.hpp"
#include "vao.hpp"

struct Mesh {
  Material *material = nullptr;
  VAO vao;
  VBO vbo;

  bool Init(const aiMesh *mesh);
  void Render(const bool transparent, const Camera &camera,
              const mat4 &modelMatrix) const;
};
