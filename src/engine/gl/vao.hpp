#pragma once

#include <functional>
#include <glad/glad.h>

using namespace std;

namespace gl {

class VAO {
private:
  GLuint id = GL_NONE;
  GLsizei count = 0;
  GLuint offset = 0;

public:
  ~VAO();
  bool Create(function<GLsizei(void)> create);
  void DrawArrays(const GLenum mode) const;
  void DrawElements(const GLenum mode) const;

  void VertexAttrib(const GLuint index, const GLint size, const GLenum type,
                    const GLboolean normalized, const GLsizei stride,
                    const GLsizei offset);
};

}