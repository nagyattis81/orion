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