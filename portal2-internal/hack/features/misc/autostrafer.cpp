#include "misc.hpp"
#include "hack/cfg/opts.hpp"

#include <algorithm>

namespace hack::features::misc {
    constexpr float kMoveLimit = 175.f;

    void autostrafer(c_usercmd* cmd) {
        if (!opts::autostrafer)
            return;

        if ((cmd->m_buttons & e_cmd_buttons::in_jump) == 0)
            return;

        if (portal::players::local->m_fFlags() & e_ent_flags::fl_onground)
            return;

        const auto new_forwardmove = 10000.f / portal::players::local->m_vecVelocity().length_2d();
        cmd->m_forwardmove = std::clamp<float>(new_forwardmove, 0.f, kMoveLimit);
        cmd->m_sidemove = ((cmd->m_mousedx && cmd->m_mousedx < 0) || !(cmd->m_number % 2)) ? -kMoveLimit : kMoveLimit;
    }
} // namespace hack::features::misc
