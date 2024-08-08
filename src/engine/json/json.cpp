#include "spdlog/spdlog.h"

#include "json.hpp"
#include "object.hpp"

#include <fstream>
#include <jsonxx.h>

namespace json {

void SaveVec3ToArray(const vec3 &value, jsonxx::Array &array) {
  array << value.x;
  array << value.y;
  array << value.z;
}

void SaveFloatToArray(const float value, jsonxx::Array &array) {
  array << value;
}

void SaveFloat(jsonxx::Object &object, const string &name, const float value) {
  object << name << value;
}

void SaveObject(jsonxx::Object &object, const string &name,
                const json::Object &obj) {
  jsonxx::Object saveObject;
  obj.Save(saveObject);
  object << name << saveObject;
}

void SaveToFile(const string &fileName, const jsonxx::Object &object) {
  spdlog::info("*** Save {}", fileName);
  fstream file;
  file.open(fileName, ios::out);
  if (!file.is_open()) {
    spdlog::critical("open error!");
    return;
  }
  std::string str = object.json();
  file << str;
  file.close();
}

void LoadArrayFromVec3(vec3 &value, const jsonxx::Array &array) {
  for (unsigned int i = 0; i < 3; i++)
    if (!array.has<jsonxx::Number>(i))
      return;
  value.x = static_cast<float>(array.get<jsonxx::Number>(0));
  value.y = static_cast<float>(array.get<jsonxx::Number>(1));
  value.z = static_cast<float>(array.get<jsonxx::Number>(2));
}

void LoadFloatFromfloat(float &value, const jsonxx::Array &array) {
  if (!array.has<jsonxx::Number>(0))
    return;
  value = static_cast<float>(array.get<jsonxx::Number>(0));
}

void LoadFloat(const jsonxx::Object &object, const string &name, float &value) {
  if (!object.has<jsonxx::Number>(name))
    return;
  value = static_cast<float>(object.get<jsonxx::Number>(name));
}

void LoadObject(const jsonxx::Object &object, const string &name,
                json::Object &obj) {
  if (!object.has<jsonxx::Object>(name))
    return;
  obj.Load(object.get<jsonxx::Object>(name));
}

jsonxx::Object *LoadFromFile(const string &fileName) {
  spdlog::info("*** Load {}", fileName);
  ifstream file(fileName);
  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  if (!file.is_open())
    return nullptr;

  jsonxx::Object *object = new jsonxx::Object();
  if (!object->parse(str)) {
    delete object;
    return nullptr;
  }

  return object;
}

} // namespace json