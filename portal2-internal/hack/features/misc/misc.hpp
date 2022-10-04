#pragma once
#include "sdk/portal.hpp"

namespace hack::features::misc {
    // callbacks
    //
    void airacceleration_fix();
    void csgolike_air_speed();
    void bhoplike_air_speed();

    // create-move
    //
    void bhop(c_usercmd* cmd);
    void autostrafer(c_usercmd* cmd);

    inline void create_move(c_usercmd* cmd) {
        autostrafer(cmd);
        bhop(cmd);
    }
} // namespace hack::features::misc