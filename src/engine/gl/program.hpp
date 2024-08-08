#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace gl {

class Program {
private:
  GLuint id = GL_NONE;
  string vsPath = "";
  string fsPath = "";

public:
  ~Program();
  bool Load(const char *vertexShaderPath, const char *fragmentShaderPath);
  void Bind() const;
  void UnBind() const;
  bool Location(GLint &location, const char *name);
};

}