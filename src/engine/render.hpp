#pragma once

#include "program.hpp"
#include "vao.hpp"

class Render {
public:
  static Render *Instance();

  bool Init();

  void Rectangle();

private:
  inline static Render *instance = nullptr;

  Program colorProgram;
  VAO quadVAO;
};
