#include "../../demo.hpp"

#include "../../engine/music.hpp"
#include "editor.hpp"

Editor::Editor(const bool enable) : disable(!enable) {}

bool Editor::Create(const CretaParameters &cretaParameters) {
  if (disable)
    return true;
  if (!Window::Create(cretaParameters))
    return false;
  return gui.Init(this->GetHandle());
}

bool Editor::Render() {
  if (disable)
    return false;
  MakeContextCurrent();
  glClear(GL_COLOR_BUFFER_BIT);
  PollEvents();
  gui.Frame();
  gui.Render();
  SwapBuffers();

  if (!Open()) {
    Delete();
    return false;
  }

  return false;
}

void Editor::Delete() { Demo::Instance()->Delete(); }