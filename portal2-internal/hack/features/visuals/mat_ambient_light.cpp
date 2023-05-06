#include "hack/cfg/opts.hpp"
#include "visuals.hpp"

#include <algorithm>

namespace hack::features::visuals {
    void mat_ambient_light() {
        static i_convar* mat_ambient_light_r = nullptr;
        static i_convar* mat_ambient_light_g = nullptr;
        static i_convar* mat_ambient_light_b = nullptr;
        static i_convar* mat_force_tonemap_scale = nullptr;

        if (!mat_ambient_light_r)
            mat_ambient_light_r = portal::cvar->find_convar("mat_ambient_light_r");

        if (!mat_ambient_light_g)
            mat_ambient_light_g = portal::cvar->find_convar("mat_ambient_light_g");

        if (!mat_ambient_light_b)
            mat_ambient_light_b = portal::cvar->find_convar("mat_ambient_light_b");

        if (!mat_force_tonemap_scale)
            mat_force_tonemap_scale = portal::cvar->find_convar("mat_force_tonemap_scale");

        if (!mat_ambient_light_r || !mat_ambient_light_g || !mat_ambient_light_b)
            return;

        if (!opts::mat_ambient_light_enabled) {
            mat_ambient_light_r->m_float_value = 0.f;
            mat_ambient_light_g->m_float_value = 0.f;
            mat_ambient_light_b->m_float_value = 0.f;
            mat_force_tonemap_scale->m_float_value = 0.f;
            return;
        }

        mat_ambient_light_r->m_float_value = opts::mat_ambient_light_value.r / 255.f;
        mat_ambient_light_g->m_float_value = opts::mat_ambient_light_value.g / 255.f;
        mat_ambient_light_b->m_float_value = opts::mat_ambient_light_value.b / 255.f;
        mat_force_tonemap_scale->m_float_value = std::clamp(opts::mat_ambient_light_value.a / 255.f, 0.01f, 1.f);
    }
} // namespace hack::features::visuals
