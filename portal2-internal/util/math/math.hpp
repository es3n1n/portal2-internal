#pragma once
#include "base.hpp"
#include "sdk/misc/ang_t.hpp"
#include "sdk/misc/vec_t.hpp"

namespace util::math {
    float normalize_pitch(float x);
    float normalize_yaw(float x);
    void movement_fix(float& forward_move, float& side_move, ang_t& angles, ang_t wish_angles);
} // namespace util::math