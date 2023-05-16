#include "hack/cfg/opts.hpp"
#include "visuals.hpp"

#include <cmath>

namespace hack::features::visuals {
    namespace {
        /*
            @note: @es3n1n:
            certified valve moment:
            I have no idea why, but the game won't allow me to query model indexes of:
                - glow01.vmt in multiplayer
                - glow1.vmt in singleplayer
            ^^^^^^^^^^^^^^^^ these are the same models by the way lol.
        */
        constexpr const char* kGlowBeamSinglePlayer = "sprites/glow1.vmt";
        constexpr const char* kGlowBeamMultiPlayer = "sprites/glow01.vmt";

        __forceinline bool create_and_draw_beam(beam_info_t& info) {
            if (auto beam = portal::beams->create_beam_points(info); beam) {
                portal::beams->render_beams(beam);
                return true;
            }

            return false;
        }

        __forceinline void draw_beam_paw(const vec3_t& src, const vec3_t& dst, const color_t& col) {
            beam_info_t beam_info = {0};

            beam_info.m_type = 0x0; // TE_BEAMPOINTS

            beam_info.m_start = src;
            beam_info.m_end = dst;

            beam_info.m_model_index = -1; // let the game search for the material
            beam_info.m_model_name = kGlowBeamMultiPlayer;

            beam_info.m_end_width = beam_info.m_width = 8.f;

            beam_info.m_fade_length = 0.f;
            beam_info.m_amplitude = 0.f;

            beam_info.m_speed = 0.f;
            beam_info.m_start_frame = 0;
            beam_info.m_frame_rate = 0.f;

            beam_info.m_r = col.r * 1.f;
            beam_info.m_g = col.g * 1.f;
            beam_info.m_b = col.b * 1.f;
            beam_info.m_brightness = col.a * 1.f;

            beam_info.m_segments = 2;
            beam_info.m_renderable = true;

            beam_info.m_life = opts::trails_life_time;
            beam_info.m_flags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE;

            // @note: @es3n1n: return if we can draw glow01 beam
            if (create_and_draw_beam(beam_info))
                return;

            // @note: @es3n1n: try glow1 if we can't query glow01 material
            beam_info.m_model_name = kGlowBeamSinglePlayer;
            create_and_draw_beam(beam_info);
        }
    } // namespace

    void trails() {
        if (!opts::trails || !portal::entitylist)
            return;

        for (int i = 0; i < portal::entitylist->get_highest_entity_index(); i++) {
            const auto ent = portal::entitylist->get_client_entity(i);
            if (!ent || !ent->is_player())
                continue;

            const vec3_t current_origin = ent->m_vecOrigin();
            draw_beam_paw(current_origin, vec3_t(current_origin.x, current_origin.y + 10.f, current_origin.z), opts::trails_color);
        }
    }
} // namespace hack::features::visuals