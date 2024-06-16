#include "spdlog/spdlog.h"

#include <glad/glad.h>

#include "window.hpp"
#include <GLFW/glfw3.h>

Window *Window::Instance() {
  if (!instance)
    instance = new Window();
  return instance;
}

Window::~Window() {
  if (window)
    glfwDestroyWindow(window);
  glfwTerminate();
}

static void callbackKey(GLFWwindow *window, int key, int, int action, int) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::Create(const Parameters &parameters) {
  if (!parameters.title) {
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
  if (!parameters.fullscreen) {
    width = mode->width / 2;
    height = mode->height / 2;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  if (parameters.samples > 0)
    glfwWindowHint(GLFW_SAMPLES, parameters.samples);
  window = glfwCreateWindow(width, height, parameters.title,
                            parameters.fullscreen ? monitor : nullptr, nullptr);
  if (!window) {
    spdlog::critical("create window error!");
    return false;
  }

  if (!parameters.fullscreen) {
    glfwSetWindowPos(window, mode->width / 2 - width / 2,
                     mode->height / 2 - height / 2);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  glfwSetKeyCallback(window, callbackKey);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(parameters.vsync ? 1 : 0);

  int version = gladLoadGL();
  if (version == 0) {
    spdlog::critical("GLAD init error!");
    return false;
  }

  spdlog::info("GLFW_WINDOW {} x {}", width, height);
  spdlog::info("GL_VENDOR   {0}", (const char *)(glGetString(GL_VENDOR)));
  spdlog::info("GL_RENDERER {0}", (const char *)(glGetString(GL_RENDERER)));
  spdlog::info("GL_VERSION  {0}", (const char *)(glGetString(GL_VERSION)));

  if (parameters.samples > 0)
    glEnable(GL_MULTISAMPLE);

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
