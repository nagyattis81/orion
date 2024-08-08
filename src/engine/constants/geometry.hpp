#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace glm;

namespace constants {

struct Geometry {
  inline static const vec3 ORIGO = vec3(0.0f);
  inline static const vec3 NORMALX = vec3(1.0f, 0.0f, 0.0f);
  inline static const vec3 NORMALY = vec3(0.0f, 1.0f, 0.0f);
  inline static const vec3 NORMALZ = vec3(0.0f, 0.0f, 1.0f);
  inline static const mat4 IDENTITY = mat4(1.0f);
};

}