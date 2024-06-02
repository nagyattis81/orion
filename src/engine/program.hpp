#pragma once

#include <glad/glad.h>

class Program {
private:
  GLuint id = GL_NONE;

public:
  ~Program();
  bool Load(const char *vertexShaderPath, const char *fragmentShaderPath);
  void Bind() const;
  void UnBind() const;
  bool Location(GLint &location, const char *name);
};