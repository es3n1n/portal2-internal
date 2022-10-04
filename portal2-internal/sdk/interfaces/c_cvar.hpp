#pragma once
#include "util/mem/mem.hpp"

class i_convar {
public:
    char __pad[0x2C];
    float m_float_value;
};

class c_cvar {
public:
    i_convar* find_convar(const char* var_name) {
        return util::mem::virtual_function<i_convar*(__thiscall*)(void*, const char*)>(this, 15)(this, var_name);
    }
};
