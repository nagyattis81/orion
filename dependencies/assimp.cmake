# https://github.com/Hoshiningen/OpenGL-Template/blob/a4e3b662d5437448324f16235e59c4ded7fb33e7/cmake/LinkASSIMP.cmake#L22
# https://github.com/search?q=FetchContent_Declare+assimp+language%3ACMake&type=code&l=CMake
# https://github.com/mfl28/opengl-cpp-starter

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.4.2
)
FetchContent_GetProperties(assimp)
if (NOT assimp_POPULATED)
    FetchContent_Populate(assimp)
    add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()

set(COMMON_INCLUDES ${COMMON_INCLUDES} ${assimp_SOURCE_DIR}/include)
set(COMMON_INCLUDES ${COMMON_INCLUDES} ${assimp_BINARY_DIR}/include)

if (WIN32)
    set(COMMON_LIBS ${COMMON_LIBS} ${assimp_BINARY_DIR}/lib/Release/assimp-vc143-mt.lib)
    configure_file(${assimp_BINARY_DIR}/bin/Release/assimp-vc143-mt.dll ${CMAKE_SOURCE_DIR}/assimp-vc143-mt.dll COPYONLY)    
elseif (APPLE)
	#
else ()
	#
endif ()