#pragma once
#include "c_base_entity.hpp"
#include <cstdint>

class c_base_player : public c_base_entity {
public:
    NETVAR(int, m_fFlags, 0xF8);
    NETVAR(int, m_iObserverMode, 0x16e4);
    NETVAR(int, m_iHealth, 0xf4);
    NETVAR(vec3_t, m_vecVelocity, 0x108);
};
