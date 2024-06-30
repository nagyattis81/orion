#include "spdlog/spdlog.h"

#include "mesh.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace std;

bool Mesh::Init(const aiMesh *mesh) {
  if (!mesh) {
    spdlog::critical("aiMesh not found");
    return false;
  }
  const auto creator = [&]() -> GLsizei {
    struct Vertex {
      vec3 position = vec3(0.0f);
      vec3 normal = vec3(0.0f);
      vec2 textureCoord = vec2(0.0f);
    };
    static const GLsizei STRIDE = sizeof(Vertex);

    vector<Vertex> vertices;
    const auto hasNormals = mesh->HasNormals();
    const auto hasTextureCoords0 = mesh->HasTextureCoords(0);
    for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
      const auto &face = mesh->mFaces[f];
      if (face.mNumIndices != 3)
        continue;
      for (unsigned int i = 0; i < face.mNumIndices; i++) {
        const auto index = face.mIndices[i];
        const auto &position = mesh->mVertices[index];
        aiVector3D normal(0.0f);
        if (hasNormals)
          normal = mesh->mNormals[index];
        aiVector3D textureCoord(0.0f);
        if (hasTextureCoords0)
          textureCoord = mesh->mTextureCoords[0][index];
        vertices.push_back(
            {.position = vec3(position.x, position.y, position.z),
             .normal = vec3(normal.x, normal.y, normal.z),
             .textureCoord = vec2(textureCoord.x, textureCoord.y)});
      }
    }

    if (!vbo.Create(sizeof(Vertex) * vertices.size(), &vertices[0].position.x))
      return 0;
    vao.VertexAttrib(0, 3, GL_FLOAT, GL_FALSE, STRIDE, 0);
    vao.VertexAttrib(1, 3, GL_FLOAT, GL_TRUE, STRIDE, sizeof(vec3));
    vao.VertexAttrib(2, 2, GL_FLOAT, GL_FALSE, STRIDE, sizeof(vec3));
    vbo.UnBind();

    return static_cast<GLsizei>(vertices.size());
  };
  return vao.Create(creator);
}

void Mesh::Render(const bool transparent, const Camera &camera,
                  const mat4 &modelMatrix) const {
  if (material->Transparent() != transparent)
    return;
  material->Bind(camera, modelMatrix);
  vao.DrawArrays(GL_TRIANGLES);
  material->UnBind();
}
