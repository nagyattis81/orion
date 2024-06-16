#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Camera::Ortho(const ivec2 &size) {
  projection = ortho(0.0f, static_cast<float>(size.x),
                     static_cast<float>(size.y), 0.0f, 0.0f, 100.0f);
}

void Camera::Perspective(const float fovy, const float aspect,
                         const float zNear, const float zFar) {
  projection = perspective(glm::radians(fovy), aspect, zNear, zFar);
}

void Camera::LookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
  view = lookAt(eye, center, up);
}

const float *Camera::View() const { return value_ptr(view); }
const float *Camera::Projection() const { return value_ptr(projection); }

mat4 Camera::MVP(const mat4 &model) const { return projection * view * model; }
