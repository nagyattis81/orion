#include "spdlog/spdlog.h"

#include "texture.hpp"

map<aiTextureType, const char *> MaterialTexture::names = {
    {aiTextureType_DIFFUSE, "DIFFUSE"},
    {aiTextureType_SPECULAR, "SPECULAR"},
    {aiTextureType_AMBIENT, "AMBIENT"},
    {aiTextureType_EMISSIVE, "EMISSIVE"},
    {aiTextureType_HEIGHT, "HEIGHT"},
    {aiTextureType_NORMALS, "NORMALS"},
    {aiTextureType_SHININESS, "SHININESS"},
    {aiTextureType_OPACITY, "OPACITY"},
    {aiTextureType_DISPLACEMENT, "DISPLACEMENT"},
    {aiTextureType_LIGHTMAP, "LIGHTMAP"},
    {aiTextureType_REFLECTION, "REFLECTION"},
    {aiTextureType_BASE_COLOR, "BASE_COLOR"},
    {aiTextureType_NORMAL_CAMERA, "NORMAL_CAMERA"},
    {aiTextureType_EMISSION_COLOR, "EMISSION_COLOR"},
    {aiTextureType_METALNESS, "METALNESS"},
    {aiTextureType_DIFFUSE_ROUGHNESS, "DIFFUSE_ROUGHNESS"},
    {aiTextureType_AMBIENT_OCCLUSION, "AMBIENT_OCCLUSION"},
    {aiTextureType_SHEEN, "SHEEN"},
    {aiTextureType_CLEARCOAT, "CLEARCOAT"},
    {aiTextureType_TRANSMISSION, "TRANSMISSION"},
    {aiTextureType_UNKNOWN, "UNKNOWN"}};

bool MaterialTexture::LoadTexture(const aiMaterial *material, string path,
                                  vector<unsigned int> &handledTextureTypes) {
  if (material->GetTextureCount(type) > 0) {
    aiString aiPath;
    material->GetTexture(type, 0, &aiPath);
    spdlog::info(" Load texture: {} {}", aiPath.C_Str(), names.at(type));
    const string fileName = path + string(aiPath.C_Str());
    if (!texture2D.Load({.fileName = fileName.c_str(), .flip = true}))
      return false;
    handledTextureTypes.push_back(type);
  } else
    texture2D.Generate(defaultTextureType);
  return true;
}

void MaterialTexture::Bind() const { texture2D.Bind(GL_TEXTURE0 + slot); }
void MaterialTexture::UnBind() const { texture2D.UnBind(); }
