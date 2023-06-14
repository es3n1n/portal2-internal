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
        color_t dark_col = color_t::black();
        for (auto* name : {"$PortalColorGradientLight", "$PortalColorGradientDark"}) {
            if (var = mat->find_var(name, &found); var && found)
                apply_color(&var->vec3, dark_col);
        }

        if (var = mat->find_var("$PortalCoopColorPlayerOnePortalOne", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[opts::portal_colors_t::PLAYER_1][opts::portal_colors_t::PORTAL_1]);

        if (var = mat->find_var("$PortalCoopColorPlayerOnePortalTwo", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[opts::portal_colors_t::PLAYER_1][opts::portal_colors_t::PORTAL_2]);

        if (var = mat->find_var("$PortalCoopColorPlayerTwoPortalOne", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[opts::portal_colors_t::PLAYER_2][opts::portal_colors_t::PORTAL_1]);

        if (var = mat->find_var("$PortalCoopColorPlayerTwoPortalTwo", &found); var && found)
            apply_color(&var->vec3, opts::portal_colors[opts::portal_colors_t::PLAYER_2][opts::portal_colors_t::PORTAL_2]);
    }

    __forceinline void patch_single_player_branch() {
        // @note: @es3n1n: we are patching the "singleplayer" branch because the game won't apply
        // our dynamic colors on the singleplayer-portal materials, dunno why and i don't want to
        // spend any more time on this
        static std::once_flag fl;
        std::call_once(fl, []() -> void {
            uint8_t patch[] = {
                0xB8, 0x37, 0x13, 0x37, 0x13, // mov eax, ptr
                0xFF, 0xE0 // jmp eax
            };

            // @todo: @es3n1n: sig the multiplayer branch instead
            *util::mem::addr_t(patch).offset(1).ptr<uintptr_t>() = portal::sig::draw_portal_single_player_color_branch.offset(-12);

            util::mem::patch_text_section(portal::sig::draw_portal_single_player_color_branch, patch, sizeof(patch));
        });
    }

    void change_portal_color() {
        if (!portal::prop_portal->m_materials.m_portal_static_overlay_tinted) // if we are not in game
            return;

        apply_color(portal::prop_portal->m_materials.m_portal_static_overlay_tinted);

        for (auto* material : portal::prop_portal->m_materials.m_portal_static_overlay)
            apply_color(material);

        apply_color(portal::prop_portal->m_materials.m_portal_depth_doubler);

        for (std::size_t i = opts::portal_colors_t::PORTAL_1; i < opts::portal_colors_t::PORTAL_MAX; i++)
            apply_color(&portal::prop_portal->m_materials.m_single_player_portal_colors[i], opts::portal_colors[0][i]);

        for (std::size_t i = opts::portal_colors_t::PLAYER_1; i < opts::portal_colors_t::PLAYER_MAX; ++i) {
            for (std::size_t j = opts::portal_colors_t::PORTAL_1; j < opts::portal_colors_t::PORTAL_MAX; ++j)
                apply_color(&portal::prop_portal->m_materials.m_coop_player_portal_colors[i][j], opts::portal_colors[i][j]);
        }

        patch_single_player_branch();
    }
} // namespace hack::features::visuals
