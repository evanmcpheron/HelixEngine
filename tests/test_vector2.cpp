#include "helix/math/Vector2.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector2 stores x and y values")
{
    const helix::math::Vector2<float> value{2.0F, 7.0F};

    REQUIRE(value.x == 2.0F);
    REQUIRE(value.y == 7.0F);
}
