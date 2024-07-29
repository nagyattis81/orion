#include "../../demo.hpp"

#include "../../engine/music.hpp"
#include "editor.hpp"

static void CallbackKey(GLFWwindow *window, int key, int, int action, int) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    static bool play = true;
    play = !play;
    Music *music = Music::Instance();
    if (play)
      music->Play();
    else
      music->Stop();
  }
}

bool Editor::Create(const CretaParameters &cretaParameters) {
  CretaParameters newCretaParameters = cretaParameters;
  newCretaParameters.keyCallback = CallbackKey;
  if (!Window::Create(newCretaParameters))
    return false;
  return gui.Init(this->GetHandle());
}

void Editor::Render() {
  MakeContextCurrent();
  glClear(GL_COLOR_BUFFER_BIT);
  PollEvents();
  gui.Frame();
  gui.Render();
  SwapBuffers();
}

void Editor::Delete() { Demo::Instance()->Delete(); }