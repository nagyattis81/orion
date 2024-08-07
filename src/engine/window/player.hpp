#pragma once

#include "window.hpp"

// TODO delete this file

class Music;
class Demo;

class Player : public Window {
private:
  Music *music = nullptr;
  Demo *demo = nullptr;

public:
  bool Create(const CreateParameters *createParameters) override;
  void Render();
};