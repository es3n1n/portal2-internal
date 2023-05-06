#pragma once
#include "util/mem/mem.hpp"
#include "sdk/structs/c_base_player.hpp"

class c_entitylist {
public:
    c_base_entity* get_client_entity(int entity_index) {
        // @xref: 55 8B EC 8B 55 08 83 FA FF 74 1E [client.dll]
        return util::mem::virtual_function<c_base_entity*(__thiscall*)(void*, int)>(this, 3)(this, entity_index);
    }

    int get_highest_entity_index() {
        auto f = util::mem::virtual_function<int(__thiscall*)(void*)>(this, 6);
        return f(this);
    }
};
