#pragma once
#include <cstdint>


class c_global_vars {
private:
    std::uint8_t __pad[0x14];
public:
    std::int32_t m_max_clients;
};
