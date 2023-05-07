#pragma once
#include "c_mat_system.hpp"
#include <cstdint>

struct prop_portal_rendering_materials_t {
    i_material* m_portal_materials[2];
    i_material* m_portal_render_fix_materials[2];
    i_material* m_portal_depth_doubler;
    i_material* m_portal_static_overlay[2];
    i_material* m_portal_static_overlay_tinted;
    i_material* m_portal_static_ghosted_overlay[2];
    i_material* m_portal_static_ghosted_overlay_tinted;
    i_material* m_portal_stencil_hole;
    i_material* m_portal_refract;

    unsigned int m_depth_double_viewmatrix_var_cache;
    unsigned int m_static_overlay_tinted_color_gradient_light_var_cache;

    vec3_t m_coop_player_portal_colors[2][2];
    vec3_t m_single_player_portal_colors[2];
};

class c_prop_portal {
public:
    prop_portal_rendering_materials_t m_materials;
};
