#pragma once

#include <vector>

class Animation {
private:
  struct Key {
    double time;
    float value;
  };
  std::vector<Key> keys;

public:
  void Push(const double time, const float value);
  float GetValue(const double time);
};
