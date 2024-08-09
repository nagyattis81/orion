#pragma once

#include "texture2d.hpp"
#include <glad/glad.h>
#include <glm/vec2.hpp>

using namespace glm;

namespace gl {

struct FBO {
  GLuint id = GL_NONE;
  ivec2 size = ivec2(0);
  Texture2D color;
  GLuint rbo = GL_NONE;

  bool Create(const ivec2 size);
  void Bind() const;
  void UnBind() const;
};

} // namespace gl