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

    void vector_angles(vec3_t& forward, ang_t& angles) {
        double tmp, yaw, pitch;

        if (forward.y == 0 && forward.x == 0) {
            yaw = 0;
            if (forward.z > 0)
                pitch = 270;
            else
                pitch = 90;
        } else {
            yaw = (math::atan2(forward.y, forward.x) * 180.0 / pi);
            if (yaw < 0.0)
                yaw += 360.0;

            tmp = math::sqrt(forward.x * forward.x + forward.y * forward.y);
            pitch = (math::atan2(-forward.z, tmp) * 180.0 / pi);
            if (pitch < 0.0)
                pitch += 360.0;
        }

        angles.x = static_cast<float>(pitch);
        angles.y = static_cast<float>(yaw);
        angles.z = 0.f;
    }

    void movement_fix(float& forwardmove, float& sidemove, ang_t& angles, ang_t wish_angles) {
        auto delta = angles.y - wish_angles.y;
        if (!delta)
            return;

        auto speed = math::sqrt(sidemove * sidemove + forwardmove * forwardmove);
        auto yaw = math::atan2(sidemove, forwardmove) + delta;

        forwardmove = static_cast<float>(math::cos(yaw) * speed);
        sidemove = static_cast<float>(math::sin(yaw) * speed);
    }
} // namespace util::math