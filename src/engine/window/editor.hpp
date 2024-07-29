#pragma once

#include "../gui.hpp"
#include "window.hpp"

class Editor : public Window {
private:
  GUI gui;

public:
  bool Create(const CretaParameters &cretaParameters) override;
  void Render() override;
  void Delete();
};