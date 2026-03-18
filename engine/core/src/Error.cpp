#include "helix/core/Error.hpp"

#include "helix/core/Log.hpp"

#include <cstdlib>
#include <string>

namespace helix::core {
namespace {

[[nodiscard]] std::string format_report(FailureReport const &report) {
  std::string message{"["};
  message += report.code;
  message += "] ";
  message += report.message;

  if (!report.action.empty()) {
    message += " | action: ";
    message += report.action;
  }

  return message;
}

} // namespace

void report_failure(FailureReport const &report, std::source_location location) {
  Logger::instance().log(LogLevel::Error, report.category, format_report(report),
                         location);
}

[[noreturn]] void report_fatal(FailureReport const &report,
                               std::source_location location) {
  Logger::instance().log(LogLevel::Fatal, report.category, format_report(report),
                         location);
  std::abort();
}

} // namespace helix::core
