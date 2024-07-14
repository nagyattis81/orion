cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(Demo)
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
	set(CMAKE_OSX_ARCHITECTURES x86_64)
	set(COMMON_LIBS opengl32 glu32)
elseif (APPLE)
	set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
	find_library(COCOA_FRAMEWORK Cocoa)
	find_library(OPENGL_FRAMEWORK OpenGL)
	find_library(CARBON_FRAMEWORK Carbon)
	find_library(IOKIT_FRAMEWORK IOKit)
	find_library(COREAUDIO_FRAMEWORK CoreAudio)
	find_library(COREVIDEO_FRAMEWORK CoreVideo)
	find_library(AVFOUNDATION_FRAMEWORK AVFoundation)
	mark_as_advanced(
		COCOA_FRAMEWORK 
		OPENGL_FRAMEWORK 
		CARBON_FRAMEWORK
		IOKIT_FRAMEWORK
		COREAUDIO_FRAMEWORK 
		COREVIDEO_FRAMEWORK 
		AVFOUNDATION_FRAMEWORK
	)
	set(COMMON_LIBS 
		${COMMON_LIBS} 
		${COCOA_FRAMEWORK} 
		${OPENGL_FRAMEWORK} 
		${CARBON_FRAMEWORK}
		${IOKIT_FRAMEWORK}
		${COREAUDIO_FRAMEWORK}
		${COREVIDEO_FRAMEWORK}
		${AVFOUNDATION_FRAMEWORK}
	)
endif ()


set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/glfw/include)
if (WIN32)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/glfw/glfw3dll.lib)
elseif (APPLE)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/glfw/apple/libglfw3.a)
else ()
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/glfw/linux/libglfw3.a)
endif ()


set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/bass)
if (WIN32)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/bass/bass.lib)
elseif (APPLE)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/bass/libbass.dylib)
else ()
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/bass/libbass.so)
endif ()

set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/stb)

##################################### GLM ######################################
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	set(COMMON_INCLUDES ${COMMON_INCLUDES} ${glm_SOURCE_DIR})
endif()

#################################### SPDLOG ####################################
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
	FetchContent_Populate(spdlog)
	set(COMMON_INCLUDES ${COMMON_INCLUDES} ${spdlog_SOURCE_DIR}/include)
endif()

set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/glad/include)
file(GLOB_RECURSE LIBS_GLAD_SRC "libs/glad/src/glad.c")
set(LIBS_SRC ${LIBS_SRC} ${LIBS_GLAD_SRC})
source_group("Library Files\\glad" FILES ${LIBS_GLAD_SRC})


set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/jsonxx)
file(GLOB_RECURSE LIBS_JSONXX_SRC "libs/jsonxx/jsonxx.cc")
set(LIBS_SRC ${LIBS_SRC} ${LIBS_JSONXX_SRC})
source_group("Library Files\\jsonxx" FILES ${LIBS_JSONXX_SRC})


set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/assimp/include)
if (WIN32)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/assimp/assimp-vc143-mt.lib)
elseif (APPLE)
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/assimp/libassimp.5.dylib)
else ()
	set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_SOURCE_DIR}/libs/assimp/libassimp.so.5)
endif ()

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

set(COMMON_SRC ${COMMON_SRC} ${LIBS_SRC})
set(DEMO_EXE "demo")
file(GLOB_RECURSE DEMO_SRC src/*.cpp)
set(DEMO_APP_SRC ${COMMON_SRC} ${DEMO_SRC})

add_executable(${DEMO_EXE} ${DEMO_APP_SRC})
target_include_directories(${DEMO_EXE} PUBLIC ${COMMON_INCLUDES})
target_link_libraries(${DEMO_EXE} ${COMMON_LIBS})
set_property(TARGET ${DEMO_EXE} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "..")
