#include "object.hpp"
#include "json.hpp"

namespace json {

struct Object::Value {
  virtual void Save(const string &name, jsonxx::Object &object) = 0;
  virtual void Load(const string &name, const jsonxx::Object &object) = 0;
};

struct ValueFloat : public Object::Value {
  float *value = nullptr;

  void Save(const string &name, jsonxx::Object &object) override {
    json::SaveFloat(object, name, *value);
  }

  void Load(const string &name, const jsonxx::Object &object) override {
    json::LoadFloat(object, name, *value);
  };
};

void Object::Float(const string &name, float *value) {
  auto store = new ValueFloat();
  store->value = value;
  values[name] = store;
}

void Object::Save(jsonxx::Object &object) const {
  for (auto it : values)
    it.second->Save(it.first, object);
}

void Object::Load(const jsonxx::Object &object) {
  for (auto it : values)
    it.second->Load(it.first, object);
}

} // namespace json