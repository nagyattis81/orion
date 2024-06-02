#include "spdlog/spdlog.h"

#include "camera.hpp"
#include "sprite.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

bool Sprite::InitTexture(const Texture2D::Parameters &parameters) {
  return texture.Load(parameters);
}

bool Sprite::InitProgram() {
  if (!program.Load("data/shaders/texture.vert", "data/shaders/texture.frag"))
    return false;
  if (!program.Location(modelViewLocation, "modelView"))
    return false;
  if (!program.Location(projectionLocation, "projection"))
    return false;
  GLint textureLocation = -1;
  if (!program.Location(textureLocation, "text"))
    return false;
  glUniform1i(textureLocation, 0);
  if (!program.Location(colorLocation, "color"))
    return false;
  return true;
}

bool Sprite::InitVAO() {
  const auto creator = [=]() -> GLsizei {
    struct Vertex {
      glm::vec2 pos = glm::vec2(0.0f);
      glm::vec2 uv = glm::vec2(0.0f);
    };
    static const GLsizei STRIDE = sizeof(Vertex);

    const auto size = texture.GetSize();

    const auto halfWidth = size.x / 2.0f;
    const auto halfHeight = size.y / 2.0f;

    const float left = -halfWidth;
    const float right = halfWidth;
    const float top = halfHeight;
    const float bottom = -halfHeight;

    static const glm::vec2 leftTop(0.0f, 1.0f);
    static const glm::vec2 rightTop(1.0f, 1.0f);
    static const glm::vec2 rightBottom(1.0f, 0.0f);
    static const glm::vec2 leftBottom(0.0f, 0.0f);

    const Vertex vertices[6] = {
        {{left, bottom}, leftBottom}, {{left, top}, leftTop},
        {{right, top}, rightTop},     {{right, bottom}, rightBottom},
        {{left, bottom}, leftBottom}, {{right, top}, rightTop}};
    if (!vbo.Create(sizeof(vertices), vertices))
      return 0;
    vao.VertexAttrib(0, 2, GL_FLOAT, GL_FALSE, STRIDE, 0);
    vao.VertexAttrib(1, 2, GL_FLOAT, GL_TRUE, STRIDE, sizeof(glm::vec2));
    vbo.UnBind();
    return 6;
  };

  return vao.Create(creator);
}

bool Sprite::Load(const Texture2D::Parameters &parameters) {
  spdlog::info("Sprite load {}", parameters.fileName);
  if (!InitTexture(parameters))
    return false;
  if (!InitProgram())
    return false;
  if (!InitVAO())
    return false;
  return true;
}

void Sprite::Render(const Camera &camera, const glm::mat4 &transformation,
                    const glm::vec4 &color) const {
  program.Bind();
  glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &transformation[0][0]);
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, camera.Projection());
  glUniform4fv(colorLocation, 1, &color.r);
  texture.Bind(GL_TEXTURE0);
  vao.DrawArrays(GL_TRIANGLES);
  texture.UnBind();
  program.UnBind();
}