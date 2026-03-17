#include "helix/core/Application.hpp"

int main() {
  helix::core::ApplicationConfig config{};
  config.app_name = "Helix Runtime";
  config.max_frames = 3;

  helix::core::Application app{config};
  return app.run();
}
