#pragma once

#include "material/material.hpp"
#include "mesh.hpp"
#include <assimp/scene.h>
#include <glm/mat4x4.hpp>

using namespace glm;
using namespace std;

class Camera;

class Scene {
private:
  const aiScene *scene = nullptr;
  vector<Mesh *> meshes;
  vector<Material *> materials;

  bool InitMaterials(const aiScene *scene, const string &texturePath);
  bool InitMeshes(const aiScene *scene);

public:
  Scene(const aiScene *scene);

  bool Init(const string &texturePath);
  void RenderNode(const Camera &camera, aiNode *node, mat4 parentTransformation,
                  const bool transparent);
  void Render(const Camera &camera, const mat4 &transformation);
};
