add_library(engine_core STATIC)

add_library(helix::engine_core ALIAS engine_core)

target_sources(
  engine_core
  PRIVATE
    src/Application.cpp
    src/Assert.cpp
    src/Error.cpp
    src/Log.cpp
)

target_include_directories(
  engine_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(HELIX_DEFAULT_ENABLE_ASSERTS OFF)
else()
  set(HELIX_DEFAULT_ENABLE_ASSERTS ON)
endif()

option(HELIX_ENABLE_ASSERTS "Enable engine assertions" ${HELIX_DEFAULT_ENABLE_ASSERTS})

target_compile_definitions(
  engine_core
  PUBLIC
    $<$<BOOL:${HELIX_ENABLE_ASSERTS}>:HELIX_ENABLE_ASSERTS=1>
)

helix_set_warnings(engine_core)
