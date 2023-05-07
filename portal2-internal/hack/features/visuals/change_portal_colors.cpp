#include "hack/cfg/opts.hpp"
#include "visuals.hpp"

#include <cmath>

namespace hack::features::visuals {
    __forceinline void apply_color(vec3_t* vec, color_t& col) {
        vec->x = col.r / 255.f;
        vec->y = col.g / 255.f;
        vec->z = col.b / 255.f;
    }

    __forceinline void apply_color(i_material* mat) {
        bool found = false;
        i_material_var* var;

        // @fixme: @es3n1n: ghetto workaround to fix lights.
        // for a proper fix we should hook DrawSimplePortalMesh(or any other shit 
        // that gets called before/at the time of applying the tinted material)
        // and replace colours there, before applying the tinted material on the 
        // portal textures.
        // we only have one tinted material for both portals, smh
        color_t dark_col = {0.f, 0.f, 0.f};
        for (auto* name : {"$PortalColorGradientLight", "$PortalColorGradientDark"}) {
            if (var = mat->find_var(name, &found); var && found)
                apply_color(&var->vec3, dark_col);
        }

        if (var = mat->find_var("$PortalCoopColorPlayerOnePortalOne", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[0][0]);

        if (var = mat->find_var("$PortalCoopColorPlayerOnePortalTwo", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[0][1]);

        if (var = mat->find_var("$PortalCoopColorPlayerTwoPortalOne", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[1][0]);

        if (var = mat->find_var("$PortalCoopColorPlayerTwoPortalTwo", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[1][1]);
    }

    void change_portal_color() {
        if (!portal::prop_portal->m_materials.m_portal_static_overlay_tinted)
            return;

        apply_color(portal::prop_portal->m_materials.m_portal_static_overlay_tinted);

        for (std::size_t i = 0; i < 2; i++)
            apply_color(portal::prop_portal->m_materials.m_portal_static_overlay[i]);

        for (std::size_t i = 0; i < 2; i++)
            apply_color(&portal::prop_portal->m_materials.m_single_player_portal_colors[i], opts::portal_colors[0][i]);

        for (std::size_t i = 0; i < 2; i++) {
            for (std::size_t j = 0; j < 2; j++)
                apply_color(&portal::prop_portal->m_materials.m_coop_player_portal_colors[i][j], opts::portal_colors[i][j]);
        }
    }
} // namespace hack::features::visuals
