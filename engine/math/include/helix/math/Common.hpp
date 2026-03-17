#pragma once

#include <cmath>
#include <cstDint>
#include <cstddef>
#include <limits>
#include <type_traits>

namespace helix::math {
template <typename T>
inline constexpr T Pi = static_cast<T>(3.14159265358979323846);

template <typename T>
inline constexpr T Epsilon = std::numeric_limits<T>::epsilon();
} // namespace helix::math
