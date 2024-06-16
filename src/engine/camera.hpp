#pragma once

#include <glm/mat4x4.hpp>

using namespace glm;

class Camera {
private:
  mat4 view = mat4(1.0f);
  mat4 projection = mat4(1.0f);

public:
  void Ortho(const ivec2 &size);
  void Perspective(const float fovy, const float aspect, const float zNear,
                   const float zFar);
  void LookAt(const vec3 &eye, const vec3 &center, const vec3 &up);

  const float *View() const;
  const float *Projection() const;
  mat4 MVP(const mat4 &model) const;
};