#pragma once

struct InputContext_t;

namespace util::valve {
    using crc32_t = unsigned int;
    using calc_cmd_crc_t = crc32_t(__thiscall*)(void*);

    inline calc_cmd_crc_t calc_cmd_crc;

    void lock_cursor();
    void unlock_cursor();
} // namespace util::valve
