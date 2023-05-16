#pragma once
#include "sdk/misc/color_t.hpp"
#include <vcruntime.h>

namespace opts {
    struct chams_opts_t {
    public:
        bool m_enabled = false;
        int m_material = 0;
        color_t m_color = {255, 255, 255};
    };

    struct portal_colors_t {
    public:
        color_t m_portal_1 = {255, 255, 100, 255};
        color_t m_portal_2 = {100, 255, 255, 255};

        color_t& operator[](size_t index) {
            switch (index) {
            case 0:
                return m_portal_1;
            default:
                return m_portal_2;
            }
        }
    };

    inline bool bhop = false;
    inline bool autostrafer = false;
    inline bool airacceleration_fix = false;
    inline float airacceleration_value = 5.f;
    inline float fov_value = 90.f;

    inline bool mat_ambient_light_enabled = false;
    inline constinit color_t mat_ambient_light_value = {0, 0, 0};

    inline bool trails = false;
    inline constinit color_t trails_color = {255, 100, 255};
    inline float trails_life_time = 1.f;

    inline constinit portal_colors_t portal_colors[2];

    inline constinit chams_opts_t portal_gun_chams;
    inline constinit chams_opts_t chell_chams;
    inline constinit chams_opts_t wheatley_chams;
} // namespace opts
