#pragma once

#include <jsonxx.h>

struct Parameter;

struct Utils {
  static void SaveToObject(jsonxx::Object &object, Parameter *parameter);
  static void LoadFromObject(const jsonxx::Object &object,
                             Parameter *parameter);
};