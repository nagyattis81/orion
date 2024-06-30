#include "color.hpp"

void MaterialColor::GetColor(const aiMaterial *material) {
  aiColor4D aiColor(0.0f);
  if (material->Get(pKey, type, idx, aiColor) == AI_SUCCESS) {
    color = vec3(aiColor.r, aiColor.g, aiColor.b);
  }
}