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

bool Player::Init() {
  if (!Create({
          .title = "player",
          .fullscreen = false,
          .width = 1280,
          .height = 720,
          .vsync = true,
          .keyCallback = CallbackKey,
          .resize = false,
      }))
    return false;
  return true;
}

void Player::Start() {
  while (Open()) {
    Render();
    PollEvents();
    SwapBuffers();
  }
}
