#pragma once

#include <glm/mat4x4.hpp>

class Camera {
private:
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

public:
  void Ortho(const float width, const float height);

  const float *View() const;
  const float *Projection() const;
  const float *VP() const;
};