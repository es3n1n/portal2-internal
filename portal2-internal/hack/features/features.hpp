#pragma once
#include "misc/misc.hpp"
#include "visuals/visuals.hpp"

namespace hack::features {
    __forceinline void create_move(c_usercmd* cmd) {
        misc::create_move(cmd);
    }

    __forceinline void draw_model_execute(c_model_render* pthis, void* ctx, void* state, model_render_info_t* info, void* matrix, void* original_dme) {
        visuals::draw_model_execute(pthis, ctx, state, info, matrix, original_dme);
    }
} // namespace hack::features
