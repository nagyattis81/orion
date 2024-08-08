#pragma once

#include <glad/glad.h>

namespace GL {

class Shader {
private:
  GLuint id = GL_NONE;

public:
  ~Shader();

  bool Load(const char *path, const GLenum type);
  void Attach(const GLuint program);
};

}