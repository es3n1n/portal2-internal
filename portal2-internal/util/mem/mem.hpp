#pragma once
#include "util/platform.hpp"

#include <cstring>
#include <optional>
#include <cstdint>

namespace util::mem {
    enum e_mem_protection : std::uint8_t {
        MEM_NONE = 0,
        MEM_READ = (1 << 0),
        MEM_WRITE = (1 << 1),
        MEM_EXECUTE = (1 << 2),

        MEM_READ_WRITE = MEM_READ | MEM_WRITE,
        MEM_EXECUTE_READ = MEM_READ | MEM_EXECUTE,
        MEM_EXECUTE_READ_WRITE = MEM_READ | MEM_WRITE | MEM_EXECUTE,
    };

    inline void** virtual_table(void* inst) {
        return *reinterpret_cast<void***>(inst);
    }

    template <typename Fn>
    inline Fn virtual_function(void* inst, size_t index) {
        return reinterpret_cast<Fn>(virtual_table(inst)[index]);
    }

    int convert_from_mem_protection(e_mem_protection protection);
    e_mem_protection convert_to_mem_protection(int protection);

    bool protect_memory(void* mem, size_t len, e_mem_protection protection);

    void patch_text_section(void* dst, const uint8_t* src, size_t len, uint8_t* orig = nullptr);

    inline size_t estimate_virtual_table_length(const uintptr_t* table_start) {
        size_t i = 0;
        while(table_start[i++])
            continue;
        return i - 1;
    }
} // namespace util::mem
