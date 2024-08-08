#pragma once

#include <map>
#include <string>

using namespace std;

namespace jsonxx {
class Object;
} // namespace jsonxx

namespace json {

struct Object {
  struct Value;
  map<string, Value *> values;
  void Float(const string &name, float *value);
  void Save(jsonxx::Object &object) const;
  void Load(const jsonxx::Object &object);
};

} // namespace json