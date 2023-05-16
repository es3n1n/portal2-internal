#pragma once
#include "sdk/structs/c_base_entity.hpp"

#include "sdk/misc/vec_t.hpp"
#include "util/mem/mem.hpp"
#include <cstdint>

enum beam_flags {
    FBEAM_STARTENTITY = 0x00000001,
    FBEAM_ENDENTITY = 0x00000002,
    FBEAM_FADEIN = 0x00000004,
    FBEAM_FADEOUT = 0x00000008,
    FBEAM_SINENOISE = 0x00000010,
    FBEAM_SOLID = 0x00000020,
    FBEAM_SHADEIN = 0x00000040,
    FBEAM_SHADEOUT = 0x00000080,
    FBEAM_ONLYNOISEONCE = 0x00000100, // Only calculate our noise once
    FBEAM_NOTILE = 0x00000200,
    FBEAM_USE_HITBOXES = 0x00000400, // Attachment indices represent hitbox indices instead when this is set.
    FBEAM_STARTVISIBLE = 0x00000800, // Has this client actually seen this beam's start entity yet?
    FBEAM_ENDVISIBLE = 0x00001000, // Has this client actually seen this beam's end entity yet?
    FBEAM_ISACTIVE = 0x00002000,
    FBEAM_FOREVER = 0x00004000,
    FBEAM_HALOBEAM = 0x00008000, // When drawing a beam with a halo, don't ignore the segments and endwidth
    FBEAM_REVERSED = 0x00010000,
};

struct beam_info_t {
public:
    int m_type;
    c_base_entity* m_start_ent;
    int m_start_attachment;
    c_base_entity* m_end_ent;
    int m_end_attachment;
    vec3_t m_start;
    vec3_t m_end;
    int m_model_index;
    const char* m_model_name;
    int m_halo_index;
    const char* m_halo_name;
    float m_halo_scale;
    float m_life;
    float m_width;
    float m_end_width;
    float m_fade_length;
    float m_amplitude;
    float m_brightness;
    float m_speed;
    int m_start_frame;
    float m_frame_rate;
    float m_r;
    float m_g;
    float m_b;
    bool m_renderable;
    int m_segments;
    int m_flags;
    vec3_t m_center;
    float m_start_radius;
    float m_end_radius;
};

static_assert(offsetof(beam_info_t, m_model_name) == 0x30);
static_assert(offsetof(beam_info_t, m_flags) == 0x78);
static_assert(offsetof(beam_info_t, m_life) == 0x40);

class i_render_beams {
public:
    void* create_beam_points(beam_info_t& info) {
        return util::mem::virtual_function<void*(__thiscall*)(void*, beam_info_t&)>(this, 12)(this, info);
    }

    void render_beams(void* info) {
        return util::mem::virtual_function<void(__thiscall*)(void*, void*)>(this, 4)(this, info);
    }
};
