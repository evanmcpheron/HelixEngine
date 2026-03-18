include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)

FetchContent_MakeAvailable(Catch2)

add_executable(helix_engine_tests
  test_vector2.cpp
)

target_link_libraries(helix_engine_tests
  PRIVATE
    helix::engine_math
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(helix_engine_tests)
