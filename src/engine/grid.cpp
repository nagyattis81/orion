#include "grid.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include <glm/vec3.hpp>

bool Grid::Init(const Parameters &parameters) {
  if (!program.Load("data/shaders/grid.vert", "data/shaders/grid.frag"))
    return false;
  if (!program.Location(mvpLocation, "mvp"))
    return false;

  const auto creator = [&]() -> GLsizei {
    struct Vertex {
      vec3 position = vec3(0.0f);
      vec3 color = vec3(0.0f);
    };
    static const GLsizei STRIDE = sizeof(Vertex);
    std::vector<Vertex> vertices;

    const auto Line = [&](const vec3 &a, const vec3 &b, const vec3 &color) {
      vertices.push_back({a, color});
      vertices.push_back({b, color});
    };

    const float size = parameters.size;
    const float scale = size / (float)parameters.count;

    for (unsigned int i = 0; i < parameters.count + 1; i++) {
      const float step = i * scale;
      const float intensity = i % parameters.thickening == 0 ? 0.75f : 0.25f;
      const vec3 color = Color::GREEN * vec3(intensity);
      Line(vec3(step, -size, 0.0f), vec3(step, size, 0.0f), color);
      Line(vec3(-size, step, 0.0f), vec3(size, step, 0.0f), color);
      Line(vec3(-step, -size, 0.0f), vec3(-step, size, 0.0f), color);
      Line(vec3(-size, -step, 0.0f), vec3(size, -step, 0.0f), color);
    }

    const auto Normal = [&](const vec3 &p, const vec3 &color) {
      Line(Geometry::ORIGO, p, color);
    };

    if (parameters.normals) {
      Normal(vec3(size, 0.0f, 0.0f), Color::RED);
      Normal(vec3(0.0f, size, 0.0f), Color::GREEN);
      Normal(vec3(0.0f, 0.0f, size), Color::BLUE);
      Normal(vec3(-size, 0.0f, 0.0f), Color::CYAN);
      Normal(vec3(0.0f, -size, 0.0f), Color::PURPLE);
      Normal(vec3(0.0f, 0.0f, -size), Color::YELLOW);
    }

    if (!vbo.Create(sizeof(Vertex) * vertices.size(), &vertices[0].position.x))
      return 0;
    vao.VertexAttrib(0, 3, GL_FLOAT, GL_FALSE, STRIDE, 0);
    vao.VertexAttrib(1, 3, GL_FLOAT, GL_TRUE, STRIDE, sizeof(vec3));
    vbo.UnBind();

    return static_cast<GLsizei>(vertices.size());
  };

  return vao.Create(creator);
}

void Grid::Render(const Camera &camera, const mat4 &model) {
  program.Bind();
  glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &camera.MVP(model)[0][0]);
  vao.DrawArrays(GL_LINES);
  program.UnBind();
}