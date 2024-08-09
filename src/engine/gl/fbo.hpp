#pragma once

#include "texture2d.hpp"
#include <functional>
#include <glad/glad.h>
#include <glm/vec2.hpp>

using namespace glm;
using namespace std;

namespace gl {

class FBO {
private:
  GLuint fbo = GL_NONE;
  GLuint mfbo = GL_NONE;
  ivec2 size = ivec2(0);
  Texture2D color;
  GLuint colorBuffer = GL_NONE;
  GLuint depthBuffer = GL_NONE;
  unsigned int samples = 0;

public:
  bool Create(const ivec2 size, const unsigned int samples = 0);
  void Render(function<void(void)> render) const;
  const Texture2D &GetColor() const;
};

} // namespace gl