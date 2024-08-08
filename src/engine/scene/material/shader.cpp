#include "shader.hpp"
#include "data.hpp"
#include "src/engine/camera.hpp"

bool Material::Shader::Load() {
  if (!program.Load("data/shaders/material.vert", "data/shaders/material.frag"))
    return false;

  if (!program.Location(mvpLocation, "uMVP"))
    return false;

  if (!program.Location(normalMatrixLocation, "uNormalMatrix"))
    return false;

  if (!program.Location(modelViewMatrixLocation, "uModelViewMatrix"))
    return false;
  return true;
}

void Material::Shader::Bind(const Camera &camera, const mat4 &modelMatrix) {
  program.Bind();
  camera.UniformMVP(mvpLocation, modelMatrix);
  camera.UniformNormal(normalMatrixLocation, modelMatrix);
  camera.UniformModelView(modelViewMatrixLocation, modelMatrix);
}

void Material::Shader::UnBind() { program.UnBind(); }
