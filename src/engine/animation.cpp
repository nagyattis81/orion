#include "animation.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

static const float PI = 2.0f * acosf(0.0f);

float Interpolate(const float min, const float max, const float value) {
  const float mu2 = (1.0f - cosf(value * PI)) / 2.0f;
  return (min * (1.0f - mu2) + max * mu2);
}

void Animation::Push(const double time, const float value) {
  keys.push_back({time, value});
}

float Animation::GetValue(const double time) {
  if (keys.empty())
    return 0.0f;
  const size_t size = keys.size() - 1;
  if (size == 0)
    return keys[0].value;
  for (unsigned int i = 0; i < size; i++) {
    const auto &prev = keys[i];
    const auto &next = keys[i + 1];
    if (prev.time <= time && time < next.time) {
      const float mu =
          static_cast<float>((time - prev.time) / (next.time - prev.time));
      return Interpolate(prev.value, next.value, mu);
    }
  }
  return 0.0f;
}