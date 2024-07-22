#pragma once

#include "window.hpp"

class EditorWindow : public Window {
public:
  static EditorWindow *Instance();

private:
  inline static EditorWindow *instance = nullptr;
};