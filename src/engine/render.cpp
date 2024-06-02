#include "render.hpp"
#include "buffers.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

GLsizei CreateQuad() {
  static const glm::vec2 vertices[4] = {{glm::vec2(1.0f, 1.0f)},
                                        {glm::vec2(1.0f, -1.0f)},
                                        {glm::vec2(-1.0f, -1.0f)},
                                        {glm::vec2(-1.0f, 1.0f)}};
  VBO vbo;
  if (!vbo.Create(sizeof(vertices), vertices))
    return 0;

  VAO::VertexAttrib(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
  static const glm::uvec3 indices[2] = {glm::uvec3(0, 1, 3),
                                        glm::uvec3(1, 2, 3)};
  IBO ibo;
  if (!ibo.Create(sizeof(indices), indices))
    return 0;

  return 2;
}

Render *Render::Instance() {
  if (!instance)
    instance = new Render();
  return instance;
}

bool Render::Init() {
  if (!colorProgram.Load("data/shaders/color.vert", "data/shaders/color.frag"))
    return false;

  if (!quadVAO.Create(CreateQuad))
    return false;

  return true;
}

void Render::Rectangle() {
  colorProgram.Bind();
  quadVAO.DrawElements(GL_TRIANGLES);
  colorProgram.UnBind();
}