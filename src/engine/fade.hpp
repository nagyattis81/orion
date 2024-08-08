#pragma once

#include "animation.hpp"
#include "gl/buffers.hpp"
#include "gl/program.hpp"
#include "gl/vao.hpp"

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