#pragma once
#include <cstdint>


class c_global_vars {
private:
    MAYBE_UNUSED_PAD std::uint8_t _pad[0x14];
public:
    std::int32_t m_max_clients;
};
