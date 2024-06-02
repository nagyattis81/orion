cmake_minimum_required(VERSION 3.10)

project(Demo)
set(CMAKE_CXX_STANDARD 20)

set(DEMO_EXE "demo")

file(GLOB_RECURSE DEMO_SRC src/*.cpp)

add_executable(${DEMO_EXE} ${DEMO_SRC})