#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    void csgolike_air_speed() {
        static auto sv_paintairacceleration = portal::cvar->find_convar("sv_paintairacceleration");

        sv_paintairacceleration->m_float_value = opts::csgolike_air_speed ? 12.f : 5.f;
    }
} // namespace hack::features::misc