cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
    Enum-Flag-Set
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(verbose)
include(compiler_id)
include(build_type)
include(git_hooks)

add_library(flagset INTERFACE)
add_library(Enum-Flag-Set::flagset ALIAS flagset)
target_compile_features(flagset INTERFACE cxx_std_17)
target_include_directories(
    flagset INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    $<INSTALL_INTERFACE:include>
)

install(TARGETS flagset EXPORT MttConfig
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
install(EXPORT MttConfig
        FILE MttConfig.cmake
        NAMESPACE Enum-Flag-Set::::
        DESTINATION lib/cmake/flagset
)
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)

enable_testing()

add_subdirectory(third-party/GTest)

add_subdirectory(test)
