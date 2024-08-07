#pragma once

#include "animation.hpp"
#include "gl/buffers.hpp"
#include "gl/program.hpp"
#include "gl/vao.hpp"

class Fade {
private:
  Program program;
  GLint alphaLocation = -1;
  VAO vao;
  VBO vbo;

public:
  Animation animation;

  bool Init();
  void Add(const double time, const float alpha);
  void Render(const double time);
};