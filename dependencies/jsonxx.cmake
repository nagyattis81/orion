FetchContent_Declare(
    jsonxx
    GIT_REPOSITORY https://github.com/hjiang/jsonxx.git
    GIT_TAG v1.0.1
)
FetchContent_GetProperties(jsonxx)
if(NOT jsonxx_POPULATED)
	FetchContent_Populate(jsonxx)
endif()

set(COMMON_INCLUDES ${COMMON_INCLUDES} ${jsonxx_SOURCE_DIR})
set(LIBS_SRC ${LIBS_SRC} ${jsonxx_SOURCE_DIR}/jsonxx.cc)
