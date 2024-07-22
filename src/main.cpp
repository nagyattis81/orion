#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "engine/gui.hpp"
#include "engine/music.hpp"
#include "engine/window/editor-window.hpp"
#include "engine/window/player-window.hpp"
#include <memory>

using namespace std;

static void CallbackKey(GLFWwindow *window, int key, int, int action, int) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    static bool play = true;
    play = !play;
    if (play)
      Music::Instance()->Play();
    else
      Music::Instance()->Stop();
  }
}

int main() {
  unique_ptr<EditorWindow> editorWindow(EditorWindow::Instance());
  if (!editorWindow->Create({.title = "editor",
                             .fullscreen = false,
                             .width = 1920,
                             .height = 1080,
                             .vsync = false}))
    return EXIT_FAILURE;

  unique_ptr<GUI> gui(GUI::Instance());
  if (!gui->Init(editorWindow->GetHandle()))
    return EXIT_FAILURE;

  unique_ptr<PlayerWindow> playerWindow(PlayerWindow::Instance());
  if (!playerWindow->Create({.title = "demo",
                             .fullscreen = false,
                             .width = 1920,
                             .height = 1080,
                             .vsync = true,
                             .samples = 4,
                             .keyCallback = CallbackKey}))
    return EXIT_FAILURE;

  unique_ptr<Demo> demo(Demo::Instance());
  spdlog::info("!!! Demo init");
  if (!demo->Init())
    return EXIT_FAILURE;

  unique_ptr<Music> music(Music::Instance());
  if (!music->Load({.path = Demo::MUSIC, .volume = Demo::MUTE ? 0.0f : 1.0f}))
    return EXIT_FAILURE;

  music->SetTime(Demo::OFFSET);
  music->Play();

  while (playerWindow->Open() && editorWindow->Open()) {
    playerWindow->MakeContextCurrent();
    playerWindow->PollEvents();
    const double time = music->GetTime();
    demo->Begin(time);
    demo->Render(time);
    demo->End(time);
    playerWindow->PollEvents();
    playerWindow->SwapBuffers();

    editorWindow->MakeContextCurrent();
    glClear(GL_COLOR_BUFFER_BIT);
    editorWindow->PollEvents();
    gui->Frame();
    gui->Render();
    editorWindow->SwapBuffers();
  }

  if (Demo::EDITOR)
    demo->Delete();

  return EXIT_SUCCESS;
}