#pragma once

#include "parameter.hpp"

struct Vec3 : public Parameters::Parameter {
  vec3 *value = nullptr;
  void GUI() override;
  void Save(jsonxx::Array &array) override;
  bool Load(const jsonxx::Array &array) override;
};