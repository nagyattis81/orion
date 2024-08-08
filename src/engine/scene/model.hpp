#pragma once

using namespace std;

struct aiScene;

struct Model {
  const aiScene *scene = nullptr;
  bool Load(const string &fileName);
};