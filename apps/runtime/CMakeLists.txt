add_executable(app_runtime)

set_target_properties(app_runtime PROPERTIES OUTPUT_NAME helix_runtime)

target_sources(
  app_runtime
  PRIVATE
    src/main.cpp
)

target_link_libraries(app_runtime PRIVATE helix::engine_core)

helix_set_warnings(app_runtime)

