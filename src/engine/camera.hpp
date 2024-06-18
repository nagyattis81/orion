#pragma once

#include <glad/glad.h>

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

  void UniformProjection(const GLint location) const;
  void UniformMVP(const GLint location, const mat4 &model) const;
  void UniformNormal(const GLint location, const mat4 &model) const;
  void UniformModelView(const GLint location, const mat4 &model) const;
};