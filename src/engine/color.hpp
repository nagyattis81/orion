#pragma once

#include <glm/vec3.hpp>

using namespace glm;

struct Color {
  inline static const vec3 BLACK = vec3(0.0f);
  inline static const vec3 RED = vec3(1.0f, 0.0f, 0.0f);
  inline static const vec3 GREEN = vec3(0.0f, 1.0f, 0.0f);
  inline static const vec3 BLUE = vec3(0.0f, 0.0f, 1.0f);
  inline static const vec3 CYAN = vec3(0.0f, 1.0f, 1.0f);
  inline static const vec3 PURPLE = vec3(1.0f, 0.0f, 1.0f);
  inline static const vec3 YELLOW = vec3(1.0f, 1.0f, 0.0f);
  inline static const vec3 WHITE = vec3(1.0f);
};