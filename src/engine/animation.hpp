#pragma once

#include <vector>

using namespace std;

class Animation {
private:
  struct Key {
    double time;
    float value;
  };
  vector<Key> keys;

public:
  void Push(const double time, const float value);
  float GetValue(const double time);
};
