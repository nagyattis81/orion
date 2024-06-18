#include "fade.hpp"
#include <glm/vec2.hpp>

using namespace glm;

bool Fade::Init() {
  if (!program.Load("data/shaders/fade.vert", "data/shaders/fade.frag"))
    return false;
  if (!program.Location(alphaLocation, "alpha"))
    return false;

  const auto creator = [&]() -> GLsizei {
    const vec2 vertices[6] = {
        {-1.0f, 1.0f},  {1.0f, 1.0f}, {-1.0f, -1.0f},
        {-1.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, -1.0f},
    };
    if (!vbo.Create(sizeof(vertices), vertices))
      return 0;
    vao.VertexAttrib(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    vbo.UnBind();
    return 6;
  };

  return vao.Create(creator);
}

void Fade::Add(const double time, const float alpha) {}

void Fade::Render(const double time) {
  const float alpha = animation.GetValue(time);
  if (alpha > 0.0) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    program.Bind();
    glUniform1f(alphaLocation, alpha);
    vao.DrawArrays(GL_TRIANGLES);
    program.UnBind();
    glDisable(GL_BLEND);
  }
}