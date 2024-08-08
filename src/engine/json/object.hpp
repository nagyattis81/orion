#pragma once

#include <map>
#include <string>

using namespace std;

namespace jsonxx {
class Object;
} // namespace jsonxx

namespace json {

class Object {
public:
  struct Property;

private:
  map<string, Property *> properties;

protected:
  void Float(const string &name, float *value);

public:
  void Save(jsonxx::Object &object) const;
  void Load(const jsonxx::Object &object);
};

} // namespace json