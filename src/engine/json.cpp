#include "spdlog/spdlog.h"

#include "json.hpp"

#include <fstream>
#include <jsonxx.h>

namespace JSON {

void ivec2ToObject(const ivec2 &value, const string &name,
                   jsonxx::Object &object) {
  jsonxx::Array array;
  array << value.x;
  array << value.y;
  object << name << array;
}

void ObjectToivec2(ivec2 &value, const string &name,
                   const jsonxx::Object &object) {
  if (!object.has<jsonxx::Array>(name))
    return;
  const auto array = object.get<jsonxx::Array>(name);
  value.x = static_cast<int>(array.get<jsonxx::Number>(0));
  value.y = static_cast<int>(array.get<jsonxx::Number>(1));
}

void vec3ToArray(const vec3 &value, jsonxx::Array &array) {
  array << value.x;
  array << value.y;
  array << value.z;
}

void ArrayTovec3(vec3 &value, const jsonxx::Array &array) {
  value.x = static_cast<float>(array.get<jsonxx::Number>(0));
  value.y = static_cast<float>(array.get<jsonxx::Number>(1));
  value.z = static_cast<float>(array.get<jsonxx::Number>(2));
}

void floatToArray(const float value, jsonxx::Array &array) { array << value; }

void ArrayTofloat(float &value, const jsonxx::Array &array) {
  value = static_cast<float>(array.get<jsonxx::Number>(0));
}

jsonxx::Object *Load(const string &fileName) {
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

void Save(const string &fileName, const jsonxx::Object &object) {
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
} // namespace JSON