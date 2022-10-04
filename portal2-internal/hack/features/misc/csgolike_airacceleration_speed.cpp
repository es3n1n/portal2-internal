#include "../../cfg/cfg.h"
#include "misc.h"

namespace hack::features::misc {
    void csgolike_air_speed() {
        static auto sv_paintairacceleration = portal::interfaces::m_cvar->find_convar("sv_paintairacceleration");

        sv_paintairacceleration->m_float_value = cfg::opts::csgolike_air_speed ? 12.f : 5.f;
    }
} // namespace hack::features::misc