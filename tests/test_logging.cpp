#include "helix/core/Error.hpp"
#include "helix/core/Log.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

namespace {

class LoggerStateGuard {
public:
  LoggerStateGuard()
      : logger_(helix::core::Logger::instance()),
        original_config_(logger_.config()) {}
  ~LoggerStateGuard() {
    logger_.reset_sink();
    logger_.configure(original_config_);
  }

private:
  helix::core::Logger &logger_;
  helix::core::LogConfig original_config_;
};

} // namespace

TEST_CASE("Logger filters messages below the configured threshold") {
  LoggerStateGuard guard{};
  auto &logger = helix::core::Logger::instance();

  std::vector<helix::core::LogRecord> records{};
  logger.configure({helix::core::LogLevel::Warn, false, false});
  logger.set_sink([&records](helix::core::LogRecord const &record) {
    records.push_back(record);
  });

  logger.log(helix::core::LogLevel::Info, "Test", "this should be filtered");
  logger.log(helix::core::LogLevel::Error, "Test", "this should survive");

  REQUIRE(records.size() == 1);
  REQUIRE(records.front().level == helix::core::LogLevel::Error);
  REQUIRE(records.front().message == "this should survive");
}

TEST_CASE("Recoverable failures include an error code and action") {
  LoggerStateGuard guard{};
  auto &logger = helix::core::Logger::instance();

  std::vector<helix::core::LogRecord> records{};
  logger.configure({helix::core::LogLevel::Trace, false, false});
  logger.set_sink([&records](helix::core::LogRecord const &record) {
    records.push_back(record);
  });

  helix::core::report_failure({helix::core::FailureSeverity::Recoverable,
                               "Core",
                               "CORE-001",
                               "Something recoverable happened.",
                               "Keep going with a safe fallback."});

  REQUIRE(records.size() == 1);
  REQUIRE(records.front().level == helix::core::LogLevel::Error);
  REQUIRE(records.front().message.find("CORE-001") != std::string::npos);
  REQUIRE(records.front().message.find("safe fallback") != std::string::npos);
}
