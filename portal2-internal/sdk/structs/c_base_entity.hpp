#pragma once
#include "sdk/misc/ang_t.hpp"
#include "sdk/misc/vec_t.hpp"

class c_base_player;
class c_clientclass;

#define NETVAR(t, n, off)                                                           \
    t& n() {                                                                        \
        return *reinterpret_cast<t*>(reinterpret_cast<std::uintptr_t>(this) + off); \
    }

class c_base_entity {
public:
    NETVAR(vec3_t, m_vecOrigin, 0x12c);
    NETVAR(ang_t, m_angRotation, 0x120);
    NETVAR(int, m_nModelIndex, 0x350);
    NETVAR(int, m_fEffects, 0xe8);
    NETVAR(int, m_iTeamNum, 0xec);

    c_clientclass* get_client_class() {
        return util::mem::virtual_function<c_clientclass*(__thiscall*)(void*)>(this, 2)(this);
    }

    bool is_player() {
        return util::mem::virtual_function<bool(__thiscall*)(void*)>(this, 149)(this);
    }
};
