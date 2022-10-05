#pragma once
#include "sdk/portal.hpp"
#include <optional>

namespace hack::features::misc {
    // callbacks
    //
    void airacceleration_fix();
    void apply_acceleration(std::optional<float> new_value = std::nullopt);

    // create-move
    //
    void bhop(c_usercmd* cmd);
    void autostrafer(c_usercmd* cmd);

    inline void create_move(c_usercmd* cmd) {
        autostrafer(cmd);
        bhop(cmd);
    }
} // namespace hack::features::misc