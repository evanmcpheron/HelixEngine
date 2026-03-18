#include "helix/core/Application.hpp"

#include "helix/core/Assert.hpp"
#include "helix/core/Error.hpp"
#include "helix/core/Log.hpp"
#include "helix/core/LogCategories.hpp"

#include <exception>
#include <utility>

namespace helix::core {

Application::Application(ApplicationConfig config)
    : config_(std::move(config)) {}

int Application::run() {
  try {
    startup();

    while (is_running_) {
      tick();
    }

    shutdown();
    return 0;
  } catch (std::exception const &exception) {
    HELIX_LOG_ERROR(log_category::Core,
                    "Unhandled std::exception escaped the runtime loop: ",
                    exception.what());
    return 1;
  } catch (...) {
    HELIX_LOG_ERROR(log_category::Core,
                    "Unhandled unknown exception escaped the runtime loop.");
    return 1;
  }
}

void Application::sanitize_config() {
  if (config_.app_name.empty()) {
    HELIX_REPORT_ERROR(
        log_category::App, "APP-001", "Application name was empty.",
        "Defaulting the application name to 'Helix Runtime'.");
    config_.app_name = "Helix Runtime";
  }

  if (config_.max_frames == 0) {
    HELIX_REPORT_ERROR(log_category::App, "APP-002",
                       "max_frames was 0, so the loop would never tick.",
                       "Clamping max_frames to 1 for the temporary runtime.");
    config_.max_frames = 1;
  }
}

void Application::startup() {
  HELIX_ASSERT(!is_running_, log_category::Assert,
               "startup() cannot be called while the application is already "
               "running.");

  sanitize_config();

  is_running_ = true;
  frame_index_ = 0;

  HELIX_LOG_INFO(log_category::Core, "Booting ", config_.app_name);
  HELIX_LOG_INFO(log_category::Core,
                 "Startup categories enabled: ", log_category::Core, ", ",
                 log_category::App, ", ", log_category::Assert);
  HELIX_LOG_DEBUG(log_category::App,
                  "Entering temporary main loop with max_frames=",
                  config_.max_frames);
}

void Application::tick() {
  HELIX_ASSERT(is_running_, log_category::Assert,
               "tick() cannot run when the application is stopped.");

  ++frame_index_;
  HELIX_LOG_TRACE(log_category::App, "Frame ", frame_index_);

  if (frame_index_ >= config_.max_frames) {
    HELIX_LOG_INFO(log_category::App,
                   "Reached requested frame limit (", config_.max_frames,
                   "). Preparing shutdown.");
    is_running_ = false;
  }
}

void Application::shutdown() {
  HELIX_LOG_INFO(log_category::Core, "Leaving main loop.");
  HELIX_LOG_INFO(log_category::Core, "Runtime closed cleanly.");
}

} // namespace helix::core
