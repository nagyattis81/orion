#include "object.hpp"
#include "json.hpp"

namespace json {

struct Object::Property {
  virtual void Save(const string &name, jsonxx::Object &object) = 0;
  virtual void Load(const string &name, const jsonxx::Object &object) = 0;
};

struct PropertyFloat : public Object::Property {
  float *value = nullptr;

  void Save(const string &name, jsonxx::Object &object) override {
    json::SaveFloat(object, name, *value);
  }

  void Load(const string &name, const jsonxx::Object &object) override {
    json::LoadFloat(object, name, *value);
  };
};

void Object::Float(const string &name, float *value) {
  auto property = new PropertyFloat();
  property->value = value;
  properties[name] = property;
}

void Object::Save(jsonxx::Object &object) const {
  for (auto it : properties)
    it.second->Save(it.first, object);
}

void Object::Load(const jsonxx::Object &object) {
  for (auto it : properties)
    it.second->Load(it.first, object);
}

} // namespace json