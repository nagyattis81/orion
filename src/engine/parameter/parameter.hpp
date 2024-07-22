#pragma once

#include "types.hpp"
#include <glm/vec3.hpp>
#include <jsonxx.h>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

class Parameter {
private:
  Type type = TYPE_COUNT;
  bool show = false;
  bool firstShow = false;
  vector<Parameter *> children;

  static void SaveToObject(jsonxx::Object &object, Parameter *parameter);
  static void LoadFromObject(const jsonxx::Object &object,
                             Parameter *parameter);
  static void HandleChildren(Parameter *parameter,
                             const Type filterType = Type::TYPE_COUNT);
  static void HandleTab(Parameter *parameter);
  static bool IsGroup(const Type type);

  void HandleWindow();
  void HandleCollapse();
  void HandleSimple();
  void HandleTabs();

protected:
  string name = "";

public:
  bool LoadFromFile();
  void SaveToFile();
  void Color3(const char *name, vec3 *color);
  void Vec3(const char *name, vec3 *value);
  void Float(const char *name, float *value, const float v_speed = 1.0f,
             const float v_min = 0.0f, const float v_max = 0.0f,
             const char *format = "%.3f");
  void Group(Parameter *parameter);
  void Set(const char *name, const Type &type);
  void HandleMenuItem(const char *name);

  virtual void GUI();
  virtual void Load(const jsonxx::Array &arr) {}
  virtual void Save(jsonxx::Array &arr) {}
};