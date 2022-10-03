#pragma once
#include "../../util/mem/mem.h"

class i_surface {
public:
    void unlock_cursor() {
        // @xref: "8B 81 ? ? ? ? 6A 00 " [vguimatsurface.dll]
        util::mem::virtual_function<void(__thiscall*)(void*)>(this, 64)(this);
    }
};