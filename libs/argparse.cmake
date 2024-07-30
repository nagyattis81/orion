FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_GetProperties(argparse)
if(NOT argparse_POPULATED)
	FetchContent_Populate(argparse)
	set(COMMON_INCLUDES ${COMMON_INCLUDES} ${argparse_SOURCE_DIR}/include)
endif()