#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

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

bool Window::Create(const char *title, unsigned int width, unsigned int height,
                    const Fullscreen fullscreen, const Vsync vsync) {
  if (!title) {
    std::cerr << "invalid window title!";
    return false;
  }

  if (!glfwInit()) {
    std::cerr << "GLFW init error!";
    return false;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (!monitor) {
    std::cerr << "primary monitor not found!";
    return false;
  }

  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  if (!mode) {
    std::cerr << "primary monitor video mode not found!";
    return false;
  }

  const bool isFullscreen = fullscreen == Fullscreen::ON;

  if (isFullscreen) {
    width = mode->width;
    height = mode->height;
  }

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(width, height, title,
                            isFullscreen ? monitor : nullptr, nullptr);
  if (!window) {
    std::cerr << "create window error!";
    return false;
  }

  if (!isFullscreen) {
    glfwSetWindowPos(window, mode->width / 2 - width / 2,
                     mode->height / 2 - height / 2);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  glfwSetKeyCallback(window, callbackKey);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(vsync == Vsync::ON ? 1 : 0);
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
