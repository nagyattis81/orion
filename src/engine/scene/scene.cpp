#include "spdlog/spdlog.h"

#include "./../camera.hpp"
#include "scene.hpp"

Scene::Scene() {
  parameters.Tab("materials");
  parameters.Tab("meshes");
}

bool Scene::InitMaterials(const string &texturePath) {
  for (unsigned int m = 0; m < scene->mNumMaterials; m++) {
    const aiMaterial *aimaterial = scene->mMaterials[m];
    if (!aimaterial) {
      spdlog::critical("{} aiMaterial not found", m);
      return false;
    }
    Material *material = new Material();
    if (!material) {
      spdlog::critical("material allocate error");
      return false;
    }
    if (!material->Init({.material = aimaterial, .texturePath = texturePath})) {
      spdlog::critical("material init error");
      return false;
    }

    materials.push_back(material);
  }
  return true;
}

bool Scene::InitMeshes() {
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *aimesh = scene->mMeshes[m];
    if (!aimesh) {
      spdlog::critical("{} aiMesh not found", m);
      return false;
    }
    Mesh *mesh = new Mesh();
    if (!mesh) {
      spdlog::critical("mesh allocate error");
      return false;
    }
    if (!mesh->Init(aimesh)) {
      spdlog::critical("mesh init error");
      return false;
    }
    mesh->material = materials[aimesh->mMaterialIndex];
    meshes.push_back(mesh);
  }
  return true;
}

bool Scene::Init(const aiScene *scene, const string &texturePath) {
  this->scene = scene;
  if (!InitMaterials(texturePath))
    return false;
  if (!InitMeshes())
    return false;
  return true;
}

void Scene::RenderNode(const Camera &camera, aiNode *node,
                       mat4 parentTransformation, const bool transparent) {

  mat4 modelMatrix{};
  modelMatrix[0][0] = node->mTransformation.a1;
  modelMatrix[1][0] = node->mTransformation.a2;
  modelMatrix[2][0] = node->mTransformation.a3;
  modelMatrix[3][0] = node->mTransformation.a4;

  modelMatrix[0][1] = node->mTransformation.b1;
  modelMatrix[1][1] = node->mTransformation.b2;
  modelMatrix[2][1] = node->mTransformation.b3;
  modelMatrix[3][1] = node->mTransformation.b4;

  modelMatrix[0][2] = node->mTransformation.c1;
  modelMatrix[1][2] = node->mTransformation.c2;
  modelMatrix[2][2] = node->mTransformation.c3;
  modelMatrix[3][2] = node->mTransformation.c4;

  modelMatrix[0][3] = node->mTransformation.d1;
  modelMatrix[1][3] = node->mTransformation.d2;
  modelMatrix[2][3] = node->mTransformation.d3;
  modelMatrix[3][3] = node->mTransformation.d4;

  modelMatrix = parentTransformation * modelMatrix;

  for (unsigned int i = 0; i < node->mNumMeshes; i++)
    meshes[node->mMeshes[i]]->Render(transparent, camera, modelMatrix);

  for (unsigned int i = 0; i < node->mNumChildren; i++)
    RenderNode(camera, node->mChildren[i], modelMatrix, transparent);
}

void Scene::Render(const Camera &camera, const mat4 &transformation) {
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  RenderNode(camera, scene->mRootNode, transformation, false);
  glEnable(GL_BLEND);
  RenderNode(camera, scene->mRootNode, transformation, true);
}
