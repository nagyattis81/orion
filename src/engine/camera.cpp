#include "camera.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera() {
  parameter.Set("camera", Type::TYPE_COLLAPSE);

  viewParameter.Set("view", Type::TYPE_TAB);
  viewParameter.Vec3("eye", &eye);
  viewParameter.Vec3("center", &center);
  viewParameter.Vec3("up", &up);
  parameter.Group(&viewParameter);

  projectionParameter.Set("projection", Type::TYPE_TAB);
  projectionParameter.Float("fovy", &fovy);
  projectionParameter.Float("aspect", &aspect);
  projectionParameter.Float("zNear", &zNear);
  projectionParameter.Float("zFar", &zFar);
  parameter.Group(&projectionParameter);
}

void Camera::Ortho() {
  projection = ortho(0.0f, static_cast<float>(size.x),
                     static_cast<float>(size.y), 0.0f, 0.0f, 100.0f);
}

void Camera::Perspective() {
  projection = perspective(glm::radians(fovy), aspect, zNear, zFar);
}

void Camera::LookAt() { view = lookAt(eye, center, up); }

void Camera::UniformProjection(const GLint location) const {
  glUniformMatrix4fv(location, 1, GL_FALSE, &projection[0][0]);
}

void Camera::UniformMVP(const GLint location, const mat4 &model) const {
  const mat4 matrix = projection * view * model;
  glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Camera::UniformNormal(const GLint location, const mat4 &model) const {
  const mat3 matrix = inverseTranspose(mat3(view * model));
  glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Camera::UniformModelView(const GLint location, const mat4 &model) const {
  const mat4 matrix = view * model;
  glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}