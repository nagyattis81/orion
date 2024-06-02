#pragma once

#include <functional>
#include <glad/glad.h>

class VAO {
private:
  GLuint id = GL_NONE;
  GLsizei count = 0;

public:
  ~VAO();
  bool Create(std::function<GLsizei(void)> create);
  void DrawArrays(const GLenum mode) const;
  void DrawElements(const GLenum mode) const;

  static void VertexAttrib(const GLuint index, const GLint size,
                           const GLenum type, const GLboolean normalized,
                           const GLsizei stride, const GLsizei offset);
};