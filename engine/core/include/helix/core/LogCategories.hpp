#pragma once

#include <string_view>

namespace helix::core::log_category {

inline constexpr std::string_view Core{"Core"};
inline constexpr std::string_view App{"App"};
inline constexpr std::string_view Assert{"Assert"};
inline constexpr std::string_view Platform{"Platform"};
inline constexpr std::string_view Render{"Render"};
inline constexpr std::string_view Asset{"Asset"};

} // namespace helix::core::log_category
