#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    void bhoplike_air_speed() {
        static auto sv_paintairacceleration = portal::cvar->find_convar("sv_paintairacceleration");

        sv_paintairacceleration->m_float_value = opts::bhoplike_air_speed ? 10000.f : 5.f;
    }
} // namespace hack::features::misc
