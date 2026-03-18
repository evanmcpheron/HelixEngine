#pragma once

#include "helix/core/Log.hpp"

#include <source_location>
#include <string>
#include <string_view>

namespace helix::core::detail {

[[noreturn]] void handle_assertion_failure(
    std::string_view expression, std::string_view category, std::string message,
    std::source_location location = std::source_location::current());

} // namespace helix::core::detail

#if defined(HELIX_ENABLE_ASSERTS) && HELIX_ENABLE_ASSERTS
#define HELIX_ASSERT(condition, category, ...)                                  \
  do {                                                                          \
    if (!(condition)) {                                                         \
      ::helix::core::detail::handle_assertion_failure(                          \
          #condition, category,                                                 \
          ::helix::core::detail::build_message(__VA_ARGS__),                    \
          std::source_location::current());                                     \
    }                                                                           \
  } while (false)
#else
#define HELIX_ASSERT(condition, category, ...)                                  \
  do {                                                                          \
    (void)sizeof(condition);                                                    \
  } while (false)
#endif

#define HELIX_UNREACHABLE(category, ...)                                        \
  ::helix::core::detail::handle_assertion_failure(                              \
      "unreachable", category,                                                  \
      ::helix::core::detail::build_message(__VA_ARGS__),                        \
      std::source_location::current())
