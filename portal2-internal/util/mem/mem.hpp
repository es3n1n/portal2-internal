#pragma once
#include "addr/addr.hpp"
#include "module/module.hpp"

namespace util::mem {
    void** virtual_table(mem::addr_t inst);

    template <typename Fn>
    Fn virtual_function(void* inst, size_t index) {
        return reinterpret_cast<Fn>(virtual_table(inst)[index]);
    }
} // namespace util::mem
