#pragma once
#include "util/mem/mem.hpp"

namespace util::hooking::detour {
    void init();
    void create(mem::addr_t& target, void* detour, void** orig);
    void create(void* target, void* detour, void** orig);
    void remove(void* target = nullptr /* nullptr = MH_ALL_HOOKS */);
} // namespace util::hooking::detour
