#include <glad/glad.h>

#include "engine/camera.hpp"
#include "engine/music.hpp"
#include "engine/sprite.hpp"
#include "engine/window.hpp"
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

int main() {

  std::unique_ptr<Window> window(Window::Instance());
  if (!window->Create({.title = "demo", .fullscreen = true, .vsync = false}))
    return EXIT_FAILURE;

  Sprite logo;
  if (!logo.Load({.fileName = "data/textures/cover_1.jpg", .flip = false}))
    return EXIT_FAILURE;

  Camera camera;
  camera.Ortho(1920.0f, 1080.0f);

  std::unique_ptr<Music> music(Music::Instance());
  if (!music->Load({.path = "data/music.mp3", .volume = 0.0f}))
    return EXIT_FAILURE;
  music->Play();

  while (window->Open()) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const float time = static_cast<float>(window->GetTime());

    const int NUM_OF_LAYERS = 32;
    for (int i = 0; i < NUM_OF_LAYERS; i++) {
      glm::mat4 m = glm::mat4(1.0f);
      m = glm::translate(m, glm::vec3(1920 / 2.0f, 1080 / 2.0f, 0.0f));
      m = glm::scale(m, glm::vec3(1.0f - i * 0.02f));
      m = glm::rotate(m, sin(time + i * 0.1f) * 0.5f, glm::vec3(0, 0, 1));
      logo.Render(camera, m, glm::vec4(i / (float)NUM_OF_LAYERS));
    }

    window->SwapBuffers();
    window->PollEvents();
  }

  return EXIT_SUCCESS;
}