#pragma once
#include "sdk/portal.hpp"

namespace hack::features::visuals {
    void chams(c_model_render* pthis, void* ctx, void* state, model_render_info_t* info, void* matrix, void* original_dme);
    void mat_ambient_light();
    void trails();
    void change_portal_color();

    inline void draw_model_execute(c_model_render* pthis, void* ctx, void* state, model_render_info_t* info, void* matrix, void* original_dme) {
        chams(pthis, ctx, state, info, matrix, original_dme);
    }

    inline void create_move(c_usercmd* cmd) {
        trails();
    }

    inline void present() {
        mat_ambient_light();
        change_portal_color();
    }
} // namespace hack::features::visuals
