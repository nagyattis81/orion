#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

class Texture2D {
private:
  GLuint id = GL_NONE;
  mutable GLenum texture = GL_NONE;
  glm::ivec2 size = glm::ivec2(-1);

public:
  struct Parameters {
    const char *fileName = nullptr;
    bool flip = false;
  };
  bool Load(const Parameters &parameters);
  void Bind(const GLenum texture) const;
  void UnBind() const;
  glm::ivec2 GetSize() const;
};