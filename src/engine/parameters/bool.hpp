#pragma once

#include "parameter.hpp"

struct Bool : public Parameters::Parameter {
  bool *value = nullptr;
  void GUI() override;
  void Save(jsonxx::Array &array) override;
  bool Load(const jsonxx::Array &array) override;
};
