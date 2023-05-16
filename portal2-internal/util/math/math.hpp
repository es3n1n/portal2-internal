#pragma once
#include "sdk/misc/ang_t.hpp"
#include "sdk/misc/vec_t.hpp"
#include "base.hpp"

namespace util::math {
    float normalize_pitch(float x);
    float normalize_yaw(float x);
    void movement_fix(float& forwardmove, float& sidemove, ang_t& angles, ang_t wish_angles);
} // namespace util::math
