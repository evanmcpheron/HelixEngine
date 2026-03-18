#pragma once

#include <cstdint>
#include <source_location>
#include <string_view>

namespace helix::core {

enum class FailureSeverity : std::uint8_t {
  Recoverable = 0,
  Fatal = 1,
};

struct FailureReport {
  FailureSeverity severity{FailureSeverity::Recoverable};
  std::string_view category;
  std::string_view code;
  std::string_view message;
  std::string_view action;
};

void report_failure(
    FailureReport const &report,
    std::source_location location = std::source_location::current());

[[noreturn]] void report_fatal(
    FailureReport const &report,
    std::source_location location = std::source_location::current());

} // namespace helix::core

#define HELIX_REPORT_ERROR(category, code, message, action)                     \
  ::helix::core::report_failure(                                                \
      {::helix::core::FailureSeverity::Recoverable, category, code, message,    \
       action},                                                                 \
      std::source_location::current())

#define HELIX_REPORT_FATAL(category, code, message, action)                     \
  ::helix::core::report_fatal(                                                  \
      {::helix::core::FailureSeverity::Fatal, category, code, message, action}, \
      std::source_location::current())
