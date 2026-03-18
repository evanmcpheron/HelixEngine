#include "helix/core/Application.hpp"
#include "helix/core/Log.hpp"
#include "helix/core/LogCategories.hpp"

using namespace helix;

int main()
{
    core::LogConfig log_config{};
    log_config.minimum_level = core::default_log_level();
    log_config.include_timestamps = false;
    log_config.include_source_location = true;

    core::Logger::instance().configure(log_config);
    HELIX_LOG_INFO(core::log_category::Core, "Logger initialized.");

    core::ApplicationConfig config{};
    config.app_name = "Helix Runtime";
    config.max_frames = 3;

    core::Application app{config};
    return app.run();
}
