#pragma once

namespace util::math {
    constexpr auto e = 2.71828182845904523536f;
    constexpr auto pi = 3.14159265358979323846f;
    constexpr auto radpi = 180.f / pi;
    constexpr auto sqrpi = pi * pi;
    constexpr auto round_error = 0.5;

    [[nodiscard]] inline double deg2rad(const double& x) {
        return x * (static_cast<double>(pi) / 180.0);
    }

    [[nodiscard]] inline double rad2deg(const double& x) {
        return x * (180.0 / static_cast<double>(pi));
    }
} // namespace util::math