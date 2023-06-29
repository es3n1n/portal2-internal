#pragma once
#include "util/math/math.hpp"
#include "util/mem/mem.hpp"

class c_view_setup {
    template <typename T = std::uint32_t>
    struct stored_value_with_backup_t {
    public:
        T value;
        T old;
    };
public:
    stored_value_with_backup_t<std::uint32_t> m_x; // 0x0
    stored_value_with_backup_t<std::uint32_t> m_y; // 0x8
    stored_value_with_backup_t<std::uint32_t> m_width; // 0x10
    stored_value_with_backup_t<std::uint32_t> m_height; // 0x18
private:
    MAYBE_UNUSED_PAD std::uint8_t _pad[0x48]; // 0x20

public:
    float_t m_fov; // 0x68
    float_t m_viewmodel_fov; // 0x6C
    vec3_t m_origin; // 0x70
    ang_t m_angles; // 0x7C
};

// @note: @es3n1n: `ClientModePortalNormal: ClientModeShared, IClientMode, CGameEventListener, IGameEventListener2`
class c_clientmode {
public:
};
