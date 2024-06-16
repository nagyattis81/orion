#include "part.hpp"

#include "constants.hpp"
#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/geometry.hpp"
#include "engine/sprite.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

struct Part01 : public Part {
  Camera camera;

  inline static const vec3 CENTER = vec3(vec2(Constants::SIZE) * 0.5f, 0.0f);

  bool Init() override {
    camera.Ortho(Constants::SIZE);
    return true;
  }

  void Render(const float globalTime) override {
    ClearColor(Color::BLACK);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    static const int NUM_OF_LAYERS = 16;
    for (int i = 0; i < NUM_OF_LAYERS; i++) {
      mat4 m = Geometry::IDENTITY;
      m = translate(m, CENTER);
      m = scale(m, vec3(1.0f - i * 0.02f));
      m = rotate(m, sinf(globalTime + i * 0.1f) * 0.5f, Geometry::NORMALZ);
      demo->logo.Render(camera, m, vec4(i / (float)NUM_OF_LAYERS));
    }
  }
};

extern Part *CreatePart01() { return new Part01(); }
