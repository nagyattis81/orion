#pragma once

#include <glm/mat4x4.hpp>
#include <string>

using namespace glm;
using namespace std;

class Scene;
class Camera;

class Model {
private:
  Scene *scene = nullptr;

public:
  struct Parameters {
    string fileName;
    string texturePath = "";
  };

  bool Load(const Parameters &parameters);
  void Render(const Camera &camera, const mat4 &transformation = mat4(1.0f));
};