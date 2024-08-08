#pragma once

#include "json.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

using namespace std;
using namespace glm;

namespace jsonxx {
class Object;
class Array;
} // namespace jsonxx

namespace json {

class Object;

void SaveVec3ToArray(const vec3 &value, jsonxx::Array &array);
void SaveFloatToArray(const float value, jsonxx::Array &array);
void SaveFloat(jsonxx::Object &object, const string &name, const float value);
void SaveObject(jsonxx::Object &object, const string &name,
                const json::Object &obj);
void SaveToFile(const string &fileName, const jsonxx::Object &object);

void LoadArrayFromVec3(vec3 &value, const jsonxx::Array &array);
void LoadFloatFromfloat(float &value, const jsonxx::Array &array);
void LoadFloat(const jsonxx::Object &object, const string &name, float &value);
void LoadObject(const jsonxx::Object &object, const string &name,
                json::Object &obj);
jsonxx::Object *LoadFromFile(const string &fileName);

} // namespace json