add_library(engine_core STATIC)

add_library(helix::engine_core ALIAS engine_core)

target_sources(
  engine_core
  PRIVATE
    src/Application.cpp
)

target_include_directories(
  engine_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

helix_set_warnings(engine_core)
