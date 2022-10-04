#pragma once
#include "util/mem/mem.hpp"

class c_engine_client {
public:
    int get_local_player() {
        return util::mem::virtual_function<int(__thiscall*)(void*)>(this, 12)(this);
    }
};
