#include "color3.hpp"
#include <imgui.h>

void Color3::GUI() { ImGui::ColorEdit3(name.c_str(), &value->r); }
