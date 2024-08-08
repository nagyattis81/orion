#pragma once

#include "src/engine/animation.hpp"
#include "src/engine/gl/buffers.hpp"
#include "src/engine/gl/program.hpp"
#include "src/engine/gl/vao.hpp"

class Fade {
private:
  gl::Program program;
  GLint alphaLocation = -1;
  gl::VAO vao;
  gl::VBO vbo;

public:
  Animation animation;

  bool Init();
  void Add(const double time, const float alpha);
  void Render(const double time);
};