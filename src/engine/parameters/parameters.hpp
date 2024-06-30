#pragma once

#include <glm/vec3.hpp>
#include <jsonxx.h>
#include <vector>

using namespace std;
using namespace glm;

class Parameters {
public:
  struct Parameter;

private:
  string type = "";
  vector<Parameter *> items;
  vector<Parameters *> children;

public:
  string name = "";
  Parameters(const string &type);
  bool LoadFromFile(const char *name);
  void SaveToFile(const char *name);
  bool LoadFromJSON(const jsonxx::Object &object);
  void SaveToJSON(jsonxx::Object &object);
  void GUI();
  void Vec3(const char *name, vec3 *value);
  void Color3(const char *name, vec3 *value);
  void Bool(const char *name, bool *value);
  void Float(const char *name, float *value, const float v_speed = 1.0f,
             const float v_min = 0.0f, const float v_max = 0.0f,
             const char *format = "%.3f");
  void Tab(const char *name);
  void Children(const vector<Parameters *> &children) {
    this->children.insert(this->children.begin(), children.begin(),
                          children.end());
  }
};
