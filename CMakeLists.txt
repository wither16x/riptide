cmake_minimum_required(VERSION 4.4)

project(riptide
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(RiptideTargets)

add_library(riptide_pch INTERFACE)
target_include_directories(riptide_pch INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_precompile_headers(riptide_pch INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/std.h"
)

add_library(riptide_warnings INTERFACE)
target_compile_options(riptide_warnings INTERFACE
    -Wall -Wextra -Wpedantic
)

add_subdirectory(riptide)