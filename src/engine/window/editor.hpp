#pragma once

#include "../gui.hpp"
#include "window.hpp"

class Editor : public Window {
private:
  bool disable = false;
  GUI gui;

public:
  Editor(const bool enable);
  bool Create(const CretaParameters &cretaParameters) override;
  bool Render();
  void Delete();
};