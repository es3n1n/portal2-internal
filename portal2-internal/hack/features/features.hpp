#pragma once
#include "misc/misc.hpp"

namespace hack::features {
    __forceinline void create_move(c_usercmd* cmd) {
        misc::create_move(cmd);
    }
} // namespace hack::features
