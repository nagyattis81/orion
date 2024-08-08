#pragma once

#include <glad/glad.h>

#include "src/engine/gl/texture2d.hpp"
#include <assimp/scene.h>
#include <map>

using namespace std;

struct MaterialTexture {
  GLuint slot;
  const aiTextureType type;
  const char *name = nullptr;
  const Texture2D::Type defaultTextureType;
  Texture2D texture2D;
  GLint location = -1;

  static map<aiTextureType, const char *> names;

  bool LoadTexture(const aiMaterial *material, string path,
                   vector<unsigned int> &handledTextureTypes);

  void Bind() const;
  void UnBind() const;
};
