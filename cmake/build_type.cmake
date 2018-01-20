# Default build type is debug.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("${CMAKE_BUILD_TYPE} build environment being generated in ${CMAKE_BINARY_DIR}")

# Prevent in-tree builds.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
message(
    FATAL_ERROR
    "In-source builds are not allowed. Create a build directory and run CMake from there. This process created the files
    `CMakeCache.txt` and the directory `CMakeFiles`. Please delete them before proceeding."
)
endif()

# Only permit DEBUG and RELEASE build types.
string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)
if (CMAKE_BUILD_TYPE AND NOT uppercase_CMAKE_BUILD_TYPE MATCHES "^(DEBUG|RELEASE)$")
message(
    FATAL_ERROR
    "Invalid value for CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}. The only valid build types are DEBUG and RELEASE."
)
endif()

