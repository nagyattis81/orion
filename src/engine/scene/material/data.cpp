#include "spdlog/spdlog.h"

#include "data.hpp"
#include "src/engine/gl/program.hpp"

static void NotSupportedTextureType(const aiMaterial *material,
                                    const aiTextureType type) {
  if (material->GetTextureCount(type) > 0) {
    aiString path;
    material->GetTexture(type, 0, &path);
    spdlog::warn("Texture type not supported {} - {} : {}",
                 MaterialTexture::names.at(type), material->GetName().C_Str(),
                 path.C_Str());
  }
}

bool Material::Data::Load(const Parameters &parameters) {
  const auto material = parameters.material;
  spdlog::info("Material init: {}", material->GetName().C_Str());
  const auto texturePath = parameters.texturePath;

  for (auto it : materialTextures) {
    for (auto itsearch : materialTextures) {
      if (it != itsearch && it->slot == itsearch->slot) {
        spdlog::critical("Texture slot cannot be equal! [{} - {}]", it->name,
                         itsearch->name);
        return false;
      }
    }
  }

  for (auto it : materialColors)
    it->GetColor(material);

  vector<unsigned int> handledTextureTypes;
  for (auto it : materialTextures) {
    if (!it->LoadTexture(material, texturePath, handledTextureTypes))
      return false;
    if (it->type == aiTextureType_OPACITY && it->texture2D.Loaded())
      transparent = true;
  }
  for (unsigned int i = 0; i < aiTextureType_UNKNOWN + 1; i++) {
    const auto found =
        find(handledTextureTypes.begin(), handledTextureTypes.end(), i) !=
        handledTextureTypes.end();
    if (found)
      continue;
    NotSupportedTextureType(material, static_cast<aiTextureType>(i));
  }

  return true;
}

bool Material::Data::Init(gl::Program &program) {
  for (auto it : materialColors) {
    string name = string("uMaterial.") + it->name;
    if (!program.Location(it->location, name.c_str()))
      return false;
  }

  for (auto it : materialTextures) {
    string name = string("uTexture.") + it->name;
    if (!program.Location(it->location, name.c_str()))
      return false;
  }

  program.Bind();
  for (auto it : materialTextures)
    glUniform1i(it->location, it->slot);
  program.UnBind();

  return true;
}

void Material::Data::Bind() const {
  for (auto it : materialColors)
    glUniform3fv(it->location, 1, &it->color.r);
  for (auto it : materialTextures)
    it->Bind();
}

void Material::Data::UnBind() const {
  for (auto it : materialTextures)
    it->UnBind();
}