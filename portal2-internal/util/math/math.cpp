#include "math.hpp"
#include "sdk/misc/ang_t.hpp"
#include "sdk/misc/vec_t.hpp"
#include <cstdlib>

namespace util::math {
    float normalize_pitch(float x) {
        while (x > 89.f)
            x -= 180.f;
        while (x < -89.f)
            x += 180.f;
        return x;
    }

    float normalize_yaw(float x) {
        while (x < -180.f)
            x += 360.f;
        while (x > 180.f)
            x -= 360.f;
        return x;
    }

    // @note: kehrazy: use std::move damn it
    void movement_fix(float& forward_move, float& side_move, const ang_t& angles, const ang_t& wish_angles) {
        const auto delta = angles.y - wish_angles.y;
        if (delta < 0.001f)
            return;

        const auto speed = std::sqrt(side_move * side_move + forward_move * forward_move);
        const auto yaw = std::atan2(side_move, forward_move) + delta;

        forwardmove = static_cast<float>(std::cos(yaw) * speed); // @note: kehrazy: float to float - should be safe
        sidemove = static_cast<float>(std::sin(yaw) * speed);
    }
} // namespace util::math