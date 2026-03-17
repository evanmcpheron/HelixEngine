#pragma once

#include <cmath>
#include <type_traits>

namespace helix::math {
template <typename T> class Vector2 {
public:
  T x{};
  T y{};

  constexpr Vector2() = default;
  constexpr Vector2(T xValue, T yValue) noexcept : x(xValue), y(yValue) {}
};
} // namespace helix::math
