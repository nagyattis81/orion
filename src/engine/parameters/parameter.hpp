#pragma once

#include "parameters.hpp"
#include <jsonxx.h>

struct Parameters::Parameter {
  const char *name = nullptr;
  virtual void GUI() = 0;
  virtual void Save(jsonxx::Array &array) {}
  virtual bool Load(const jsonxx::Array &array) { return true; };
};