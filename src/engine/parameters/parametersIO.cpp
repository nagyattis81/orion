#include "parameter.hpp"
#include "parameters.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <fstream>
#include <imgui.h>

using namespace std;

static auto FOLDER = "data/parameters/";
static auto PARAMETERS_NAME_NAME = "name";
static auto PARAMETERS_TYPE_NAME = "type";
static auto PARAMATER_ARRAY_NAME = "parameters";
static auto PARAMATER_NAME_NAME = "name";
static auto PARAMATER_VALUE_NAME = "value";
static auto PARAMATER_CHILD_ARRAY_NAME = "children";

bool Parameters::LoadFromFile(const char *name) {
  const string fileName = FOLDER + string(name) + ".json";
  spdlog::info("*** Load {}", fileName);

  ifstream file(fileName);
  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  if (!file.is_open())
      return true;

  jsonxx::Object object;
  if (!object.parse(str))
    return false;

  if (!LoadFromJSON(object))
    return false;

  return true;
}

void Parameters::SaveToFile(const char *name) {
  filesystem::create_directory(FOLDER);
  const string fileName = FOLDER + string(name) + ".json";
  spdlog::info("*** Save {}", fileName);

  fstream file;
  file.open(fileName, ios::out);
  if (!file.is_open()) {
    spdlog::critical("open error!");
    return;
  }

  jsonxx::Object object;
  SaveToJSON(object);

  std::string str = object.json();
  file << str;
  file.close();
}

bool Parameters::LoadFromJSON(const jsonxx::Object &object) {
  if (object.has<jsonxx::Array>(PARAMATER_ARRAY_NAME)) {
    const jsonxx::Array &array =
        object.get<jsonxx::Array>(PARAMATER_ARRAY_NAME);
    for (unsigned int i = 0; i < array.size(); i++) {
      const jsonxx::Object &itemObject = array.get<jsonxx::Object>(i);
      if (!itemObject.has<jsonxx::String>(PARAMATER_NAME_NAME) &&
          !itemObject.has<jsonxx::String>(PARAMATER_VALUE_NAME))
        continue;
      const string name = itemObject.get<jsonxx::String>(PARAMATER_NAME_NAME);
      for (auto it : items) {
        if (it->name == name) {
          if (!it->Load(itemObject.get<jsonxx::Array>(PARAMATER_VALUE_NAME)))
            return false;
          break;
        }
      }
    }
  }

  if (object.has<jsonxx::Array>(PARAMATER_CHILD_ARRAY_NAME)) {
    const jsonxx::Array &array =
        object.get<jsonxx::Array>(PARAMATER_CHILD_ARRAY_NAME);
    for (unsigned int i = 0; i < array.size(); i++) {
      const jsonxx::Object &childObject = array.get<jsonxx::Object>(i);
      if (!children[i]->LoadFromJSON(childObject))
        return false;
    }
  }

  return true;
}

void Parameters::SaveToJSON(jsonxx::Object &object) {
  object << PARAMETERS_NAME_NAME << name;
  object << PARAMETERS_TYPE_NAME << type;

  jsonxx::Array parameterArray;
  for (auto it : items) {
    jsonxx::Object itemObject;
    itemObject << PARAMATER_NAME_NAME << it->name;
    jsonxx::Array itemValueArray;
    it->Save(itemValueArray);
    itemObject << PARAMATER_VALUE_NAME << itemValueArray;
    parameterArray << itemObject;
  }
  object << PARAMATER_ARRAY_NAME << parameterArray;

  jsonxx::Array childArray;
  for (auto it : children) {
    jsonxx::Object childObject;
    it->SaveToJSON(childObject);
    childArray << childObject;
  }

  object << PARAMATER_CHILD_ARRAY_NAME << childArray;
}
