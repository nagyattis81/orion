#include "part.hpp"

#include <glad/glad.h>

#include "engine/camera.hpp"
#include "engine/sprite.hpp"
#include <glm/gtc/matrix_transform.hpp>

struct Part01 : public Part {
  Camera camera;
  glm::vec3 clearColor = glm::vec3(0.0f);

  Part01(const glm::vec3 &clearColor) : clearColor(clearColor) {}

  bool Init() override {
    camera.Ortho(Demo::WIDTH, Demo::HEIGHT);
    return true;
  }

  void Render(const double globalTime) override {
    const float timeg = static_cast<float>(globalTime);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    static const int NUM_OF_LAYERS = 16;
    for (int i = 0; i < NUM_OF_LAYERS; i++) {
      glm::mat4 m = glm::mat4(1.0f);
      m = glm::translate(
          m, glm::vec3(Demo::WIDTH / 2.0f, Demo::HEIGHT / 2.0f, 0.0f));
      m = glm::scale(m, glm::vec3(1.0f - i * 0.02f));
      m = glm::rotate(m, sinf(timeg + i * 0.1f) * 0.5f,
                      glm::vec3(0.0f, 0.0f, 1.0f));
      demo->logo.Render(camera, m, glm::vec4(i / (float)NUM_OF_LAYERS));
    }
  }
};

extern Part *CreatePart01(const glm::vec3 &clearColor) {
  return new Part01(clearColor);
}
