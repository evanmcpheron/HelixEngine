#include "helix/core/Assert.hpp"

#include "helix/core/LogCategories.hpp"

#include <cstdlib>

namespace helix::core::detail {

[[noreturn]] void handle_assertion_failure(std::string_view expression,
                                           std::string_view category,
                                           std::string message,
                                           std::source_location location) {
  std::string full_message = "Assertion failed: [";
  full_message += expression;
  full_message += "]";

  if (!message.empty()) {
    full_message += " | ";
    full_message += message;
  }

  Logger::instance().log(LogLevel::Fatal, category, full_message, location);
  std::abort();
}

} // namespace helix::core::detail
