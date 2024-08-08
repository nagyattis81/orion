#include "buffers.hpp"

namespace gl {

Buffers::Buffers(const GLenum target) : target(target) {}

bool Buffers::Create(GLsizeiptr size, const void *data, GLenum usage) {
  if (id != GL_NONE)
    return false;
  glGenBuffers(1, &id);
  if (id == GL_NONE)
    return false;
  Bind();
  glBufferData(target, size, data, usage);
  return true;
}

void Buffers::Bind() const { glBindBuffer(target, id); }

void Buffers::UnBind() const { glBindBuffer(target, GL_NONE); }

} // namespace gl