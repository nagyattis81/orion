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