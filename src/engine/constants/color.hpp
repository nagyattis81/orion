#pragma once

#include <glm/vec3.hpp>

using namespace glm;

namespace constants {

struct Color {
  inline static const vec3 BLACK = vec3(0.0f);
  inline static const vec3 DARKGRAY = vec3(0.25f);
  inline static const vec3 GRAY = vec3(0.5f);
  inline static const vec3 LIGHTGRAY = vec3(0.5f);
  inline static const vec3 RED = vec3(1.0f, 0.0f, 0.0f);
  inline static const vec3 GREEN = vec3(0.0f, 1.0f, 0.0f);
  inline static const vec3 LIGHTBLUE = vec3(0.0f, 0.0f, 0.5f);
  inline static const vec3 BLUE = vec3(0.0f, 0.0f, 1.0f);
  inline static const vec3 CYAN = vec3(0.0f, 1.0f, 1.0f);
  inline static const vec3 PURPLE = vec3(1.0f, 0.0f, 1.0f);
  inline static const vec3 YELLOW = vec3(1.0f, 1.0f, 0.0f);
  inline static const vec3 WHITE = vec3(1.0f);
  inline static const vec3 EDITOR_BACKGROUND =
      vec3(14.0f / 255.0f, 14.0f / 255.0f, 14.0f / 255.0f);
};

} // namespace constants