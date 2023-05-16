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

    void movement_fix(float& forwardmove, float& sidemove, ang_t& angles, ang_t wish_angles) {
        auto delta = angles.y - wish_angles.y;
        if (delta < 0.001f)
            return;

        auto speed = math::sqrt(sidemove * sidemove + forwardmove * forwardmove);
        auto yaw = math::atan2(sidemove, forwardmove) + delta;

        forwardmove = static_cast<float>(math::cos(yaw) * speed);
        sidemove = static_cast<float>(math::sin(yaw) * speed);
    }
} // namespace util::math