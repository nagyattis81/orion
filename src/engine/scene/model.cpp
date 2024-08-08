#include "spdlog/spdlog.h"

#include "model.hpp"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

bool Model::Load(const std::string &fileName) {
  spdlog::info("Model load {}", fileName);
  scene = aiImportFile(fileName.c_str(), aiProcessPreset_TargetRealtime_Fast);
  if (!scene || !scene->mRootNode ||
      scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
    spdlog::critical("{}", aiGetErrorString());
    return false;
  }
  return true;
}
