set(COMMON_INCLUDES ${COMMON_INCLUDES} ${CMAKE_SOURCE_DIR}/libs/glad/include)
file(GLOB_RECURSE LIBS_GLAD_SRC "libs/glad/src/glad.c")
set(LIBS_SRC ${LIBS_SRC} ${LIBS_GLAD_SRC})
source_group("Library Files\\glad" FILES ${LIBS_GLAD_SRC})