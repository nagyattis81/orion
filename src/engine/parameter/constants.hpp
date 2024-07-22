#pragma once

#include "types.hpp"
#include <string>

using namespace std;

struct Constants {
  static inline auto FOLDER = "data/parameters/";
  static inline const string TYPE_NAMES[Type::TYPE_COUNT] = {
      "window", "collapse", "tab", "color3", "vec3", "float",
  };
};