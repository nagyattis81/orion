#pragma once

#include <glad/glad.h>

namespace gl {

class Buffers {
public:
private:
  GLuint id = 0;
  GLenum target = GL_NONE;

protected:
  Buffers(const GLenum target);

public:
  bool Create(GLsizeiptr size, const void *data, GLenum usage = GL_STATIC_DRAW);
  void Bind() const;
  void UnBind() const;
};

class VBO : public Buffers {
public:
  VBO() : Buffers(GL_ARRAY_BUFFER) {}
};

class IBO : public Buffers {
public:
  IBO() : Buffers(GL_ELEMENT_ARRAY_BUFFER) {}
};

}