#pragma once

#include <glad/glad.h>

#include "./../../gl/texture2d.hpp"
#include <assimp/scene.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

using namespace glm;
using namespace std;

struct Camera;

class Material {
public:
  struct Parameters {
    const aiMaterial *material;
    const string &texturePath;
  };

private:
  float opacity = 1.0f;
  GLenum sfactor = GL_ONE;
  GLenum dfactor = GL_ONE;

  struct Data;
  Data *data = nullptr;

  struct Shader;
  Shader *shader = nullptr;

public:
  bool Init(const Parameters &parameters);
  bool Transparent() const;
  void Bind(const Camera &camera, const mat4 &modelMatrix);
  void UnBind();
};
