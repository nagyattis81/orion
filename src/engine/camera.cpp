#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Camera::Ortho(const float width, const float height) {
  projection = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 100.0f);
}

const float *Camera::View() const { return glm::value_ptr(view); }
const float *Camera::Projection() const { return glm::value_ptr(projection); }

const float *Camera::VP() const {
  static const auto vp = projection * view;
  return glm::value_ptr(vp);
}