add_library(engine_math STATIC)

add_library(helix::engine_math ALIAS engine_math)

target_sources(
  engine_math
  PRIVATE
  src/Math.cpp
)

target_include_directories(
  engine_math
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

helix_set_warnings(engine_math)
