#pragma once
#include "sdk/misc/ang_t.hpp"
#include "util/game/game.hpp"
#include <cstdint>

class c_usercmd {
public:
    virtual ~c_usercmd(){};
    int32_t m_number; // for matching server and client commands for debugging
    int32_t m_tickcount; // the tick the client created this command
    ang_t m_viewangles; // player instantaneous view angles
    float m_forwardmove; //	forward velocity
    float m_sidemove; //  sideways velocity
    float m_upmove; //  upward velocity
    int32_t m_buttons; // attack button states
    char impulse; // impulse command issued
    char __pad[10];
    int32_t m_randomseed; // for shared random functions
    int16_t m_mousedx; // mouse accum in x from create move
    int16_t m_mousedy; // mouse accum in y from create move
    bool m_predicted; // tracks whether we've predicted this command at least once
    int __pad2[8];
};

class c_verified_usercmd {
public:
    c_usercmd m_command;
    util::game::crc32_t m_crc32;
};
