#include "utils.hpp"
#include "constants.hpp"
#include "parameter.hpp"

void Utils::SaveToObject(jsonxx::Object &object, Parameter *parameter) {
  jsonxx::Object data;
  data << "type" << Constants::TYPE_NAMES[parameter->type];

  if (parameter->type == Type::TYPE_WINDOW)
    data << "show" << parameter->show;

  if (parameter->type != Type::TYPE_WINDOW) {
    jsonxx::Array arr;
    parameter->Save(arr);
    data << "value" << arr;
  }

  if (!parameter->children.empty()) {
    jsonxx::Object children;
    for (auto it : parameter->children)
      SaveToObject(children, it);
    data << "children" << children;
  }
  object << parameter->name << data;
}

void Utils::LoadFromObject(const jsonxx::Object &object, Parameter *parameter) {
  if (!object.has<jsonxx::Object>(parameter->name))
    return;
  const auto data = object.get<jsonxx::Object>(parameter->name);

  if (!data.has<jsonxx::String>("type"))
    return;

  const string typeStr = data.get<jsonxx::String>("type");
  Type type = Type::TYPE_COUNT;
  for (unsigned int i = 0; i < Type::TYPE_COUNT; i++) {
    if (typeStr == Constants::TYPE_NAMES[i]) {
      type = Type(i);
      break;
    }
  }
  if (type == Type::TYPE_COUNT || parameter->type != type)
    return;

  if (data.has<jsonxx::Boolean>("show"))
    parameter->show = data.get<jsonxx::Boolean>("show");

  if (data.has<jsonxx::Array>("value"))
    parameter->Load(data.get<jsonxx::Array>("value"));

  if (!data.has<jsonxx::Object>("children"))
    return;
  const auto children = data.get<jsonxx::Object>("children");

  for (auto it : parameter->children) {
    Utils::LoadFromObject(children, it);
  }
}
