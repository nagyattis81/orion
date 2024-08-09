#include "spdlog/spdlog.h"

#include "texture2d.hpp"
#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gl {

struct Format {
  GLint internalformat = GL_RGBA8;
  GLenum format = GL_RGBA;
};

static Format GetFormat(const int comp) {
  Format format;
  switch (comp) {
  case 1:
    format.internalformat = GL_R8;
    format.format = GL_RED;
    break;
  case 2:
    format.internalformat = GL_RG8;
    format.format = GL_RG;
    break;
  case 3:
    format.internalformat = GL_RGB8;
    format.format = GL_RGB;
    break;
  case 4:
    format.internalformat = GL_RGBA8;
    format.format = GL_RGBA;
    break;
  default:
    spdlog::critical("comp not supported: {}", comp);
    exit(1);
  }
  return format;
};

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
  spdlog::info(" {} x {} : {}", width, height, comp);

  if (id != GL_NONE)
    glDeleteTextures(1, &id);

  glGenTextures(1, &id);
  if (id == GL_NONE) {
    spdlog::critical("generate error");
    return false;
  }
  const auto format = GetFormat(comp);

  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, format.internalformat, width, height, 0,
               format.format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  stbi_image_free(data);

  size = ivec2(width, height);

  loaded = true;
  return true;
}

void Texture2D::Generate(const Type &type) {
  unsigned char data[4] = {0, 0, 0, 0};
  if (type == Texture2D::WHITE) {
    data[0] = 255;
    data[1] = 255;
    data[2] = 255;
    data[3] = 255;
  }
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               data);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
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

ivec2 Texture2D::GetSize() const { return size; }

bool Texture2D::Loaded() const { return loaded; }

void Texture2D::Delete() {
  if (id == GL_NONE)
    return;
  glDeleteTextures(1, &id);
  id = GL_NONE;
}

void Texture2D::Create(const ivec2 size, const unsigned int filter,
                       const int internalformat, const unsigned int format,
                       const unsigned int type, const void *pixels) {
  this->size = size;
  if (id != GL_NONE) {
    glDeleteTextures(1, &id);
    id = GL_NONE;
  }
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
  glTexImage2D(GL_TEXTURE_2D, 0, internalformat, size.x, size.y, 0, format,
               type, pixels);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetNearest() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetLinear() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetClampToEdge() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetClampToBorder() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetClampToRepeat() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::GenerateMipmap() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps now!!!
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::SetMipmap() const {
  if (id == GL_NONE)
    return;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture2D::Framebuffer(const GLenum attachment, const GLint level) const {
  glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, id, level);
}

void Texture2D::ImGuiImage(const float x, const float y) const {
  ImGui::Image((void *)(intptr_t)id, ImVec2(x, y), ImVec2(0, 1), ImVec2(1, 0));
}

} // namespace gl