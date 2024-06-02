#include "spdlog/spdlog.h"

#include "texture2d.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool Texture2D::Load(const Parameters &parameters) {
  spdlog::info("Texture2D load {}", parameters.fileName);
  int width = -1, height = -1, comp;
  stbi_set_flip_vertically_on_load(parameters.flip);
  unsigned char *data =
      stbi_load(parameters.fileName, &width, &height, &comp, 0);
  if (!data || width == -1 || height == -1) {
    spdlog::critical("load error");
    return false;
  }

  if (id != GL_NONE)
    glDeleteTextures(1, &id);

  glGenTextures(1, &id);
  if (id == GL_NONE) {
    spdlog::critical("generate error");
    return false;
  }

  const bool bit32 = comp > 3;
  const GLint internalformat = bit32 ? GL_RGBA8 : GL_RGB8;
  const GLenum format = bit32 ? GL_RGBA : GL_RGB;

  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  stbi_image_free(data);

  size = glm::ivec2(width, height);

  return true;
}

void Texture2D::Bind(const GLenum texture) const {
  if (id == GL_NONE)
    return;
  this->texture = texture;
  glActiveTexture(texture);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::UnBind() const {
  if (texture == GL_NONE)
    return;
  glActiveTexture(texture);
  texture = GL_NONE;
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

glm::ivec2 Texture2D::GetSize() const { return size; }