#include "spdlog/spdlog.h"
#include <glad/glad.h>

#include "./../music.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>

#include "../../demo.hpp"

Window::~Window() {
  if (window)
    glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::Create(const CreateParameters &createParameters) {
  if (!createParameters.title) {
    spdlog::critical("invalid window title!");
    return false;
  }

  if (!glfwInit()) {
    spdlog::critical("GLFW init error!");
    return false;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (!monitor) {
    spdlog::critical("primary monitor not found!");
    return false;
  }

  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  if (!mode) {
    spdlog::critical("primary monitor video mode not found!");
    return false;
  }

  unsigned int width = mode->width;
  unsigned int height = mode->height;
  if (!createParameters.fullscreen) {
    width = static_cast<unsigned int>(createParameters.width < 0
                                          ? mode->width * 0.75f
                                          : createParameters.width);
    height = static_cast<unsigned int>(createParameters.height < 0
                                           ? mode->height * 0.75f
                                           : createParameters.height);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, createParameters.resize);
  if (createParameters.samples > 0)
    glfwWindowHint(GLFW_SAMPLES, createParameters.samples);
  window = glfwCreateWindow(width, height, createParameters.title,
                            createParameters.fullscreen ? monitor : nullptr,
                            nullptr);
  if (!window) {
    spdlog::critical("create window error!");
    return false;
  }

  if (!createParameters.fullscreen) {
    glfwSetWindowPos(window,
                     createParameters.x < 0 ? mode->width / 2 - width / 2
                                            : createParameters.x,
                     createParameters.y < 0 ? mode->height / 2 - height / 2
                                            : createParameters.y);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  if (createParameters.keyCallback)
    glfwSetKeyCallback(window, createParameters.keyCallback);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(createParameters.vsync ? 1 : 0);

  int version = gladLoadGL();
  if (version == 0) {
    spdlog::critical("GLAD init error!");
    return false;
  }

  spdlog::info("GLFW_WINDOW {} x {}", width, height);
  spdlog::info("GL_VENDOR   {0}", (const char *)(glGetString(GL_VENDOR)));
  spdlog::info("GL_RENDERER {0}", (const char *)(glGetString(GL_RENDERER)));
  spdlog::info("GL_VERSION  {0}", (const char *)(glGetString(GL_VERSION)));

  if (createParameters.samples > 0)
    glEnable(GL_MULTISAMPLE);

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

bool Window::Open() const {
  if (window)
    return !glfwWindowShouldClose(window);
  return false;
}

void Window::SwapBuffers() const {
  if (window)
    glfwSwapBuffers(window);
}

void Window::PollEvents() const { glfwPollEvents(); }

double Window::GetTime() const { return glfwGetTime(); }

void Window::SetWindowTitle(const char *title) {
  if (window && title)
    glfwSetWindowTitle(window, title);
}

void Window::Render() {
  const double time = music->GetTime();
  demo->Render(time);
  demo->End(time);
}

void Window::MakeContextCurrent() const { glfwMakeContextCurrent(window); }

ivec2 Window::GetPosition() const {
  ivec2 position;
  glfwGetWindowPos(window, &position.x, &position.y);
  return position;
}
ivec2 Window::GetSize() const {
  ivec2 size;
  glfwGetWindowSize(window, &size.x, &size.y);
  return size;
}
