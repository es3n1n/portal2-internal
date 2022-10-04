#pragma once
#include "../../../sdk/portal.h"

namespace hack::features::misc {
    // callbacks
    //
    void airacceleration_fix();
    void csgolike_air_speed();

    // create-move
    //
    void bhop(c_usercmd* cmd);
    void autostrafer(c_usercmd* cmd);

    inline void create_move(c_usercmd* cmd) {
        bhop(cmd);
        autostrafer(cmd);
    }
} // namespace hack::features::misc