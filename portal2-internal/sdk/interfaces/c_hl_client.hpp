#pragma once
#include "sdk/misc/client_class.hpp"
#include "util/mem/mem.hpp"

class c_hl_client {
public:
    c_clientclass* get_all_classes() {
        return util::mem::virtual_function<c_clientclass*(__thiscall*)(void*)>(this, 8)(this);
    };
};
