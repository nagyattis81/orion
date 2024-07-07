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

  bool InitMaterials(const string &texturePath);
  bool InitMeshes();

  void RenderNode(const Camera &camera, aiNode *node, mat4 parentTransformation,
                  const bool transparent);

public:
  Scene();
  bool Init(const aiScene *scene, const string &texturePath);
  void Render(const Camera &camera, const mat4 &transformation);
};
