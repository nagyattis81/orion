#pragma once

#include "./../demo.hpp"
#include "geometry.hpp"
#include "parameter/parameter.hpp"
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

using namespace glm;

struct Camera {
  vec3 eye = vec3(5.0f);
  vec3 center = vec3(0.0f);
  vec3 up = Geometry::NORMALZ;
  float fovy = 60.0f;
  float aspect = Demo::ASPECT;
  float zNear = 0.1f;
  float zFar = 1000.0f;
  ivec2 size = Demo::SIZE;
  mat4 view = mat4(1.0f);
  mat4 projection = mat4(1.0f);
  Parameter parameter;
  Parameter viewParameter;
  Parameter projectionParameter;

  Camera();
  void Ortho();
  void Perspective();
  void LookAt();
  void UniformProjection(const GLint location) const;
  void UniformMVP(const GLint location, const mat4 &model) const;
  void UniformNormal(const GLint location, const mat4 &model) const;
  void UniformModelView(const GLint location, const mat4 &model) const;
};