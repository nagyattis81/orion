#include "editor-window.hpp"

EditorWindow *EditorWindow::Instance() {
  if (!instance)
    instance = new EditorWindow();
  return instance;
}