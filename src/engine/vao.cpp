#include "spdlog/spdlog.h"

#include "vao.hpp"

VAO::~VAO() {
  if (id != GL_NONE)
    glDeleteVertexArrays(1, &id);
  id = GL_NONE;
}

bool VAO::Create(function<GLsizei(void)> create) {
  if (id != GL_NONE) {
    spdlog::critical("VAO invalid id!");
    return false;
  }

  glGenVertexArrays(1, &id);
  if (id == GL_NONE) {
    spdlog::critical("VAO generate error!");
    return false;
  }
  glBindVertexArray(id);
  offset = 0;
  count = create();

  glBindVertexArray(GL_NONE);
  const bool success = count > 0;
  if (!success)
    spdlog::critical("VAO vertex not found!");
  return success;
}

void VAO::DrawArrays(const GLenum mode) const {
  if (id == GL_NONE || count == 0)
    return;
  glBindVertexArray(id);
  glDrawArrays(mode, 0, count);
  glBindVertexArray(GL_NONE);
}

void VAO::DrawElements(const GLenum mode) const {
  if (id == GL_NONE || count == 0)
    return;
  glBindVertexArray(id);
  glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(GL_NONE);
}

void VAO::VertexAttrib(const GLuint index, const GLint size, const GLenum type,
                       const GLboolean normalized, const GLsizei stride,
                       const GLsizei offset) {
  this->offset += offset;
  glVertexAttribPointer(index, size, type, normalized, stride,
                        ((char *)nullptr + (this->offset)));
  glEnableVertexAttribArray(index);
}