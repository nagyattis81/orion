FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
	FetchContent_Populate(stb)
endif()

set(COMMON_INCLUDES ${COMMON_INCLUDES} ${stb_SOURCE_DIR})
