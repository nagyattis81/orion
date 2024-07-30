#pragma once

#include "parameter.hpp"
#include <glm/vec3.hpp>

using namespace glm;

struct Color3 : public Parameter {
  vec3 *value = nullptr;
  void GUI() override;
  void Load(const jsonxx::Array &array) override;
  void Save(jsonxx::Array &array) override;
};