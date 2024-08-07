#include "gui.hpp"
#include "./../demo.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

GUI *GUI::Instance(GLFWwindow *window) {
  if (!instance)
    instance = new GUI(window);
  return instance;
}

GUI::GUI(GLFWwindow *window) : window(window) {}

bool GUI::Init() {
  if (!window)
    return false;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.FontGlobalScale = 1.5;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");
  return true;
}

void GUI::Render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  static bool showDemoWindow = false;
  auto demo = Demo::Instance();
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Parts")) {
      demo->Menu();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Tools")) {
      if (ImGui::MenuItem("ImGui::Demo", nullptr, showDemoWindow))
        showDemoWindow = !showDemoWindow;
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
  if (showDemoWindow)
    ImGui::ShowDemoWindow(&showDemoWindow);
  demo->Windows();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
