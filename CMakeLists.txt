cmake_minimum_required(VERSION 3.10)

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


set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/glad/include)
file(GLOB_RECURSE LIBS_GLAD_SRC "libs/glad/src/glad.c")
set(LIBS_SRC ${LIBS_SRC} ${LIBS_GLAD_SRC})
source_group("Library Files\\glad" FILES ${LIBS_GLAD_SRC})
set(COMMON_SRC ${COMMON_SRC} ${LIBS_SRC})


set(DEMO_EXE "demo")
file(GLOB_RECURSE DEMO_SRC src/*.cpp)
set(DEMO_APP_SRC ${COMMON_SRC} ${DEMO_SRC})

add_executable(${DEMO_EXE} ${DEMO_APP_SRC})
target_include_directories(${DEMO_EXE} PUBLIC ${COMMON_INCLUDES})
target_link_libraries(${DEMO_EXE} ${COMMON_LIBS})