#include "color3.hpp"
#include <imgui.h>

void Color3::GUI() { ImGui::ColorEdit3(name, &value->r); }
