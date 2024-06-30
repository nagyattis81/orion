#include "spdlog/spdlog.h"

#include "data.hpp"
#include "material.hpp"
#include "shader.hpp"

bool Material::Init(const Parameters &parameters) {
  const aiMaterial *material = parameters.material;

  if (!data) {
    data = new Data();
    if (!data->Load(parameters))
      return false;
  }

  aiBlendMode blendMode;
  material->Get(AI_MATKEY_BLEND_FUNC, blendMode);
  if (blendMode == aiBlendMode_Default) {
    sfactor = GL_SRC_ALPHA;
    dfactor = GL_ONE_MINUS_SRC_ALPHA;
  }

  static Shader *common = nullptr;
  if (!common) {
    common = new Shader();
    if (!common->Load())
      return false;
  }
  shader = common;

  if (!data->Init(shader->program))
    return false;

  return true;
}

bool Material::Transparent() const {
  return opacity < 1.0f || data->transparent;
}

void Material::Bind(const Camera &camera, const mat4 &modelMatrix) {
  glBlendFunc(sfactor, dfactor);
  shader->Bind(camera, modelMatrix);
  data->Bind();
}

void Material::UnBind() {
  data->UnBind();
  shader->UnBind();
}
