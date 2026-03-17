#include "helix/core/Application.hpp"

#include <iostream>

namespace helix::core {

Application::Application(ApplicationConfig config)
    : config_(std::move(config)) {}

int Application::run() {
  startup();

  while (is_running_) {
    tick();
  }

  shutdown();
  return 0;
}

void Application::startup() {
  is_running_ = true;
  frame_index_ = 0;

  std::cout << "[startup] booting " << config_.app_name << '\n';
  std::cout << "[startup] entering temporary main loop" << '\n';
}

void Application::tick() {
  ++frame_index_;
  std::cout << "[tick] frame " << frame_index_ << '\n';

  if (frame_index_ >= config_.max_frames) {
    is_running_ = false;
  }
}

void Application::shutdown() {
  std::cout << "[shutdown] leaving main loop" << '\n';
  std::cout << "[shutdown] runtime closed cleanly" << '\n';
}

} // namespace helix::core
