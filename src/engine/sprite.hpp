#pragma once

#include "gl/buffers.hpp"
#include "gl/program.hpp"
#include "gl/texture2d.hpp"
#include "gl/vao.hpp"
#include <glm/mat4x4.hpp>

using namespace glm;

struct Camera;

class Sprite {
private:
  gl::Texture2D texture;
  gl::Program program;
  GLint modelViewLocation = -1;
  GLint projectionLocation = -1;
  GLint colorLocation = -1;
  gl::VAO vao;
  gl::VBO vbo;

  bool InitTexture(const gl::Texture2D::Parameters &parameters);
  bool InitProgram();
  bool InitVAO();

public:
  bool Load(const gl::Texture2D::Parameters &parameters);
  void Render(const Camera &camera, const mat4 &modelMatrix,
              const vec4 &color) const;
};