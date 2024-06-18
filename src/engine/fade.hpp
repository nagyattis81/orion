#pragma once

#include "animation.hpp"
#include "buffers.hpp"
#include "program.hpp"
#include "vao.hpp"

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