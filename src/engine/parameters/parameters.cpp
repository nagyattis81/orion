#include "spdlog/spdlog.h"

#include "bool.hpp"
#include "color3.hpp"
#include "float.hpp"
#include "parameter.hpp"
#include "parameters.hpp"
#include "vec3.hpp"

using namespace std;

Parameters::Parameters(const string &type) : type(type) {}

template <typename V, typename T>
T *Push(vector<Parameters::Parameter *> &items, const char *name, V *value) {
  auto parameter = new T();
  parameter->name = name;
  parameter->value = value;
  items.push_back(parameter);
  return parameter;
}

void Parameters::Vec3(const char *name, vec3 *value) {
  Push<vec3, ::Vec3>(items, name, value);
}

void Parameters::Color3(const char *name, vec3 *value) {
  Push<vec3, ::Color3>(items, name, value);
}

void Parameters::Bool(const char *name, bool *value) {
  Push<bool, ::Bool>(items, name, value);
}

void Parameters::Float(const char *name, float *value, const float v_speed,
                       const float v_min, const float v_max,
                       const char *format) {
  ::Float *parameter = Push<float, ::Float>(items, name, value);
  parameter->v_speed = v_speed;
  parameter->v_min = v_min;
  parameter->v_max = v_max;
  parameter->format = format;
}

void Parameters::Tab(const char *name) {}
