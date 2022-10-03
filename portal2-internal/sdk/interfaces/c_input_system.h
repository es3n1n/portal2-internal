#pragma once
#include "../../util/mem/mem.h"
#include "../structs/c_usercmd.h"

class c_input_system {
public:
    void enable_input(bool state) {
        // @xref: "55 8B EC 8A 45 08 88 81 ? ? ? ? 5D C2 04 00 55 8B EC 0F B6 81" [inputsystem.dll]
        util::mem::virtual_function<void(__thiscall*)(void*, bool)>(this, 11)(this, state);
    }

    void reset_input_state() {
        // @xref: "56 57 68 ? ? ? ? 6A 00 " [inputsystem.dll]
        util::mem::virtual_function<void(__thiscall*)(void*)>(this, 28)(this);
    }

    void get_raw_mouse_accumulators(int* x, int* y) {
        util::mem::virtual_function<void(__thiscall*)(void*, int*, int*)>(this, 50)(this, x, y); // GetRawMouseAccumulators
    }
};
