cmake_minimum_required(VERSION 4.2.3)

project(
  HelixEngine
  VERSION 0.0.1
  DESCRIPTION "A game engine written in C++"
  LANGUAGES C CXX
)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(cmake/Options.cmake)
include(cmake/CompilerWarnings.cmake)

add_subdirectory(engine/core)
add_subdirectory(engine/math)
add_subdirectory(apps/runtime)
add_subdirectory(apps/editor)
add_subdirectory(tests)
