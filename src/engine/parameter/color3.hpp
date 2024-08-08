#pragma once

#include "parameter.hpp"
#include "vec3.hpp"
#include <glm/vec3.hpp>

using namespace glm;

struct Color3 : public Vec3 {
  void GUI() override;
};