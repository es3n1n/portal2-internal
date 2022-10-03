#pragma once

struct InputContext_t;

namespace util::valve {
    namespace crc {
        typedef unsigned int crc32_t;

        using _get_checksum_fn = crc32_t(__thiscall*)(void*);
        inline _get_checksum_fn calc;
    } // namespace crc

    namespace {
        inline InputContext_t* context = nullptr;
    }

    void lock_cursor();
    void unlock_cursor();
} // namespace util::valve
