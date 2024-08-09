#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

using namespace glm;

namespace gl {

class Texture2D {
private:
  GLuint id = GL_NONE;
  mutable GLenum texture = GL_NONE;
  ivec2 size = ivec2(-1);
  bool loaded = false;

public:
  enum Type { WHITE, BLACK };

  struct Parameters {
    const char *fileName = nullptr;
    bool flip = false;
  };
  bool Load(const Parameters &parameters);
  void Generate(const Type &type);
  void Bind(const GLenum texture) const;
  void UnBind() const;
  ivec2 GetSize() const;
  bool Loaded() const;
  void Delete();
  void Create(const ivec2 size, const unsigned int filter,
              const int internalformat, const unsigned int format,
              const unsigned int type = GL_UNSIGNED_BYTE,
              const void *pixels = nullptr);

  void SetNearest() const;
  void SetLinear() const;
  void SetClampToEdge() const;
  void SetClampToBorder() const;
  void SetClampToRepeat() const;
  void GenerateMipmap() const;
  void SetMipmap() const;
  void Framebuffer(const GLenum attachment, const GLint level = GL_NONE) const;
  void ImGuiImage(const float x, const float y);
};

} // namespace gl