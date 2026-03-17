#pragma once

#include <cstdint>
#include <string>

namespace helix::core {

/**
 * Configuration for the temporary runtime application.
 *
 * Until windowing is added, max_frames gives the loop a deliberate exit path.
 */
struct ApplicationConfig {
  std::string app_name{"Helix Runtime"};
  std::uint32_t max_frames{3};
};

/**
 * Minimal runtime application used to prove the project can boot, run, and
 * shut down cleanly before SDL or rendering are introduced.
 */
class Application {
public:
  explicit Application(ApplicationConfig config);

  /** Runs the startup, frame loop, and shutdown sequence. */
  int run();

private:
  void startup();
  void tick();
  void shutdown();

  ApplicationConfig config_;
  bool is_running_{false};
  std::uint32_t frame_index_{0};
};

} // namespace helix::core
