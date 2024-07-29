#pragma once

#include "window.hpp"

class Music;
class Demo;

class Player : public Window {
private:
  Music *music = nullptr;
  Demo *demo = nullptr;

public:
  bool Create(const CretaParameters &cretaParameters) override;
  void Render() override;
};