#pragma once

#include "buffers.hpp"
#include "program.hpp"
#include "texture2d.hpp"
#include "vao.hpp"
#include <glm/mat4x4.hpp>

class Camera;

class Sprite {
private:
  Texture2D texture;
  Program program;
  GLint modelViewLocation = -1;
  GLint projectionLocation = -1;
  GLint colorLocation = -1;
  VAO vao;
  VBO vbo;

  bool InitTexture(const Texture2D::Parameters &parameters);
  bool InitProgram();
  bool InitVAO();

public:
  bool Load(const Texture2D::Parameters &parameters);
  void Render(const Camera &camera, const glm::mat4 &transformation,
              const glm::vec4 &color) const;
};