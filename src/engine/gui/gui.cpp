#include "gui.hpp"
#include "src/demo.hpp"
#include "src/engine/json/json.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

static auto FILE_NAME = "data/gui.json";

extern void Settings(bool *show);

GUI *GUI::Instance(GLFWwindow *window) {
  if (!instance)
    instance = new GUI(window);
  return instance;
}

GUI::GUI(GLFWwindow *window) : window(window) {}

bool GUI::Init(const float scale) {
  if (!window)
    return false;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.FontGlobalScale = scale;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");
  return true;
}

void GUI::Menu() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Parts")) {
      Demo::Instance()->Menu();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("ImGui::Demo", nullptr, show.demoWindow))
        show.demoWindow = !show.demoWindow;
      if (ImGui::MenuItem("Settings", nullptr, show.settings))
        show.settings = !show.settings;
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

void GUI::Windows() {
  if (show.demoWindow)
    ImGui::ShowDemoWindow(&show.demoWindow);
  if (show.settings)
    Settings(&show.settings);

  Demo::Instance()->Windows();
}

void GUI::Render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  Menu();
  Windows();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
