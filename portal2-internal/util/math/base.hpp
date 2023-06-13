#pragma once
#include "util/cast/cast.hpp"

#include <limits>
#include <numbers>

namespace util::math {
    constexpr auto e = std::numbers::e;
    constexpr auto pi = std::numbers::pi;
    constexpr auto radpi = 180.f / pi;
    constexpr auto sqrpi = pi * pi;
    constexpr auto round_error = std::numeric_limits<double>::round_error();

    [[nodiscard]] inline double deg2rad(const double& x) {
        return x * (static_cast<double>(pi) / 180.0);
    }

    [[nodiscard]] inline double rad2deg(const double& x) {
        return x * (180.0 / static_cast<double>(pi));
    }
} // namespace util::math