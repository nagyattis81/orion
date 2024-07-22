set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/imgui)
file(GLOB_RECURSE LIBS_IMGUI_SRC 
	libs/imgui/imgui.cpp
	libs/imgui/imgui_demo.cpp
	libs/imgui/imgui_draw.cpp
	libs/imgui/imgui_widgets.cpp
	libs/imgui/imgui_tables.cpp
	libs/imgui/backends/imgui_impl_glfw.cpp
	libs/imgui/backends/imgui_impl_opengl3.cpp
)
set(LIBS_SRC ${LIBS_SRC} ${LIBS_IMGUI_SRC})
source_group("Library Files\\imgui" FILES ${LIBS_IMGUI_SRC})