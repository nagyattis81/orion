#pragma once

#include "material.hpp"

#include "color.hpp"
#include "texture.hpp"

using namespace std;

class Program;

struct Material::Data {
  typedef vector<MaterialColor *> MaterialColors;
  typedef vector<MaterialTexture *> MaterialTextures;

  bool transparent = false;

  MaterialColors materialColors = {
      new MaterialColor({vec3(0.2f), "ambient", AI_MATKEY_COLOR_AMBIENT}),
      new MaterialColor({vec3(0.8f), "diffuse", AI_MATKEY_COLOR_DIFFUSE}),
  };

  MaterialTextures materialTextures = {
      new MaterialTexture(
          {0, aiTextureType_AMBIENT, "ambient", Texture2D::BLACK}),
      new MaterialTexture(
          {1, aiTextureType_DIFFUSE, "diffuse", Texture2D::WHITE}),
  };

  bool Load(const Parameters &parameters);
  bool Init(Program &program);
  void Bind() const;
  void UnBind() const;
};
