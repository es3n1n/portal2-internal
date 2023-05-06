#include "hack/cfg/opts.hpp"
#include "visuals.hpp"

namespace hack::features::visuals {
    namespace {
        __forceinline bool create_and_draw_beam(beam_info_t& info) {
            if (auto beam = portal::beams->create_beam_points(info); beam) {
                portal::beams->render_beams(beam);
                return true;
            }

            return false;
        }

        /*
            @note: @es3n1n:
            For some mysterious reasons the game won't allow me to query a model index
            of "sprites/glow1.vmt" in multiplayer, but "sprites/glow01.vmt" instead.
            And as you may predict already, for the same mysterious reason glow01 won't
            work in singleplayer.
        */
        constexpr const char* kGlowBeamSinglePlayer = "sprites/glow1.vmt";
        constexpr const char* kGlowBeamMultiPlayer = "sprites/glow01.vmt";

        __forceinline void draw_beam_paw(vec3_t src, vec3_t end, color_t col) {
            beam_info_t beam_info;
            beam_info.m_type = 0x0; // TE_BEAMPOINTS
            beam_info.m_start = src;
            beam_info.m_end = end;

            beam_info.m_model_index = -1;
            beam_info.m_model_name = kGlowBeamMultiPlayer;

            beam_info.m_width = 4.5f;
            beam_info.m_end_width = 4.5f;

            beam_info.m_fade_length = 0.5f;

            beam_info.m_amplitude = 0.f;
            beam_info.m_brightness = 255.f;

            beam_info.m_speed = 0.f;
            beam_info.m_start_frame = 0;
            beam_info.m_frame_rate = 0.f;

            beam_info.m_r = col.r * 1.f;
            beam_info.m_g = col.g * 1.f;
            beam_info.m_b = col.b * 1.f;

            beam_info.m_segments = 2;
            beam_info.m_renderable = true;

            beam_info.m_life = 1.f;
            beam_info.m_flags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;

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

            const auto origin = ent->m_vecOrigin();
            draw_beam_paw(origin, vec3_t(origin.x, origin.y + 10.f, origin.z), opts::trails_color);
        }
    }
} // namespace hack::features::visuals