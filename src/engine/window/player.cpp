#include "spdlog/spdlog.h"

#include "../../demo.hpp"
#include "../../engine/music.hpp"

#include "player.hpp"

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

bool Player::Create(const CretaParameters &cretaParameters) {

  CretaParameters newCretaParameters = cretaParameters;
  newCretaParameters.keyCallback = CallbackKey;

  if (!Window::Create(newCretaParameters))
    return false;

  demo = Demo::Instance();
  spdlog::info("!!! Demo init");
  if (!demo->Init())
    return false;

  music = Music::Instance();
  if (!music->Load({.path = Demo::MUSIC, .volume = Demo::MUTE ? 0.0f : 1.0f}))
    return false;

  music->SetTime(Demo::OFFSET);
  music->Play();
  return true;
}

void Player::Render() {
  MakeContextCurrent();
  PollEvents();
  const double time = music->GetTime();
  demo->Begin(time);
  demo->Render(time);
  demo->End(time);
  PollEvents();
  SwapBuffers();
}
