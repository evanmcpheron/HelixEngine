#pragma once

#include <chrono>
#include <concepts>
#include <cstdint>
#include <functional>
#include <mutex>
#include <ostream>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace helix::core {

enum class LogLevel : std::uint8_t {
  Trace = 0,
  Debug = 1,
  Info = 2,
  Warn = 3,
  Error = 4,
  Fatal = 5,
};

[[nodiscard]] constexpr LogLevel default_log_level() noexcept {
#ifdef NDEBUG
  return LogLevel::Info;
#else
  return LogLevel::Trace;
#endif
}

[[nodiscard]] constexpr std::string_view to_string(LogLevel level) noexcept {
  switch (level) {
  case LogLevel::Trace:
    return "TRACE";
  case LogLevel::Debug:
    return "DEBUG";
  case LogLevel::Info:
    return "INFO";
  case LogLevel::Warn:
    return "WARN";
  case LogLevel::Error:
    return "ERROR";
  case LogLevel::Fatal:
    return "FATAL";
  }

  return "UNKNOWN";
}

[[nodiscard]] constexpr bool should_log(LogLevel level,
                                        LogLevel threshold) noexcept {
  return static_cast<std::uint8_t>(level) >=
         static_cast<std::uint8_t>(threshold);
}

struct LogConfig {
  LogLevel minimum_level{default_log_level()};
  bool include_timestamps{false};
  bool include_source_location{true};
};

struct LogRecord {
  LogLevel level{LogLevel::Info};
  std::string category;
  std::string message;
  std::string timestamp;
  std::string file_name;
  std::uint_least32_t line{0};
  std::string function_name;
};

class Logger {
public:
  using Sink = std::function<void(LogRecord const &)>;

  static Logger &instance();

  void configure(LogConfig config);
  [[nodiscard]] LogConfig config() const;

  void set_sink(Sink sink);
  void reset_sink();

  void log(LogLevel level, std::string_view category, std::string message,
           std::source_location location = std::source_location::current());

private:
  Logger();

  static void default_sink(LogRecord const &record);

  mutable std::mutex mutex_;
  LogConfig config_{};
  Sink sink_{};
};

namespace detail {

inline std::string build_message() { return {}; }

template <typename... Args>
[[nodiscard]] std::string build_message(Args &&...args) {
  std::ostringstream stream;
  (stream << ... << std::forward<Args>(args));
  return stream.str();
}

template <typename... Args>
inline void log_message(LogLevel level, std::string_view category,
                        std::source_location location, Args &&...args) {
  Logger::instance().log(level, category,
                         build_message(std::forward<Args>(args)...), location);
}

} // namespace detail

} // namespace helix::core

#define HELIX_LOG_TRACE(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Trace, category, \
                                     std::source_location::current(),          \
                                     __VA_ARGS__)

#define HELIX_LOG_DEBUG(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Debug, category, \
                                     std::source_location::current(),          \
                                     __VA_ARGS__)

#define HELIX_LOG_INFO(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Info, category, \
                                     std::source_location::current(),         \
                                     __VA_ARGS__)

#define HELIX_LOG_WARN(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Warn, category, \
                                     std::source_location::current(),         \
                                     __VA_ARGS__)

#define HELIX_LOG_ERROR(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Error, category, \
                                     std::source_location::current(),          \
                                     __VA_ARGS__)

#define HELIX_LOG_FATAL(category, ...)                                          \
  ::helix::core::detail::log_message(::helix::core::LogLevel::Fatal, category, \
                                     std::source_location::current(),          \
                                     __VA_ARGS__)
