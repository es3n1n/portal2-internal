#pragma once
#include "sdk/misc/color_t.hpp"

namespace opts {
    struct chams_opts_t {
    public:
        bool m_enabled = false;
        int m_material = 0;
        color_t m_color = {255, 255, 255};
    };

    inline bool bhop = false;
    inline bool autostrafer = false;
    inline bool airacceleration_fix = false;
    inline float airacceleration_value = 5.f;
    inline float fov_value = 90.f;

    inline bool mat_ambient_light_enabled = false;
    inline constinit color_t mat_ambient_light_value = {0, 0, 0};
    
    inline constinit chams_opts_t portal_gun_chams;
    inline constinit chams_opts_t chell_chams;
    inline constinit chams_opts_t wheatley_chams;
} // namespace hack::cfg::opts
