#pragma once

#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/vec3.hpp>

using namespace glm;

struct MaterialColor {
  vec3 color;
  const char *name = nullptr;
  const char *pKey;
  unsigned int type;
  unsigned int idx;
  GLint location = -1;
  void GetColor(const aiMaterial *material);
};
