#include "helix/core/Log.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <utility>

namespace helix::core {
namespace {

[[nodiscard]] std::string basename(std::string_view path) {
  const std::size_t separator_index = path.find_last_of("/\\");
  if (separator_index == std::string_view::npos) {
    return std::string{path};
  }

  return std::string{path.substr(separator_index + 1)};
}

[[nodiscard]] std::string format_timestamp() {
  const auto now = std::chrono::system_clock::now();
  const std::time_t calendar_time = std::chrono::system_clock::to_time_t(now);

  std::tm local_time{};
#if defined(_WIN32)
  localtime_s(&local_time, &calendar_time);
#else
  localtime_r(&calendar_time, &local_time);
#endif

  std::ostringstream stream;
  stream << std::put_time(&local_time, "%H:%M:%S");
  return stream.str();
}

} // namespace

Logger &Logger::instance() {
  static Logger logger{};
  return logger;
}

Logger::Logger() : config_{}, sink_{&Logger::default_sink} {}

void Logger::configure(LogConfig config) {
  std::scoped_lock lock{mutex_};
  config_ = config;
}

LogConfig Logger::config() const {
  std::scoped_lock lock{mutex_};
  return config_;
}

void Logger::set_sink(Sink sink) {
  std::scoped_lock lock{mutex_};
  sink_ = std::move(sink);
}

void Logger::reset_sink() {
  std::scoped_lock lock{mutex_};
  sink_ = &Logger::default_sink;
}

void Logger::log(LogLevel level, std::string_view category, std::string message,
                 std::source_location location) {
  Sink sink;
  LogRecord record{};

  {
    std::scoped_lock lock{mutex_};
    if (!should_log(level, config_.minimum_level)) {
      return;
    }

    sink = sink_;
    record.level = level;
    record.category = std::string{category};
    record.message = std::move(message);

    if (config_.include_timestamps) {
      record.timestamp = format_timestamp();
    }

    if (config_.include_source_location) {
      record.file_name = basename(location.file_name());
      record.line = location.line();
      record.function_name = std::string{location.function_name()};
    }
  }

  sink(record);
}

void Logger::default_sink(LogRecord const &record) {
  std::ostream &stream =
      should_log(record.level, LogLevel::Error) ? std::cerr : std::cout;

  if (!record.timestamp.empty()) {
    stream << '[' << record.timestamp << ']';
  }

  stream << '[' << to_string(record.level) << ']';
  stream << '[' << record.category << "] ";
  stream << record.message;

  if (!record.file_name.empty()) {
    stream << " (" << record.file_name << ':' << record.line << ')';
  }

  stream << '\n';
}

} // namespace helix::core
