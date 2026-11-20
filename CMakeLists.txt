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

add_library(riptide_headers INTERFACE)
target_include_directories(riptide_headers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(riptide_reflection INTERFACE)
target_compile_options(riptide_reflection INTERFACE -freflection)

add_library(riptide_warnings INTERFACE)
target_compile_options(riptide_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wno-non-virtual-dtor
    -Wcast-qual -Wconversion -Wsign-conversion -Wold-style-cast
)

add_subdirectory(riptide)