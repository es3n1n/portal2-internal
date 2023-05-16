#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    void apply_acceleration(const std::optional<float>& new_value) {
        static auto sv_paintairacceleration = portal::cvar->find_convar("sv_paintairacceleration");

        sv_paintairacceleration->m_float_value = opts::airacceleration_value = new_value.value_or(opts::airacceleration_value);
    }
} // namespace hack::features::misc
