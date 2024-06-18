#include "spdlog/spdlog.h"

#include "model.hpp"
#include "scene.hpp"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

bool Model::Load(const Parameters &parameters) {
  spdlog::info("Scene load {}", parameters.fileName);
  const aiScene *aiscene = aiImportFile(parameters.fileName.c_str(),
                                        aiProcessPreset_TargetRealtime_Fast);
  if (!aiscene || !aiscene->mRootNode ||
      aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
    spdlog::critical("{}", aiGetErrorString());
    return false;
  }
  scene = new Scene(aiscene);
  if (!scene)
    return false;
  return scene->Init(parameters.texturePath);
}

void Model::Render(const Camera &camera, const mat4 &transformation) {
  if (scene)
    scene->Render(camera, transformation);
}
