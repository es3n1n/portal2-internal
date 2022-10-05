#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    void autostrafer(c_usercmd* cmd) {
        if (!opts::autostrafer)
            return;

        if ((cmd->m_buttons & e_cmd_buttons::in_jump) == 0)
            return;

        if (util::players::local->m_fFlags() & e_ent_flags::fl_onground)
            return;

        cmd->m_forwardmove =
            (10000.f / util::players::local->m_vecVelocity().length_2d() > 175.f) ? 175.f : 10000.f / util::players::local->m_vecVelocity().length_2d();
        cmd->m_sidemove = (cmd->m_mousedx != 0) ? (cmd->m_mousedx < 0.0f) ? -175.f : 175.f : (cmd->m_number % 2) == 0 ? -175.f : 175.f;
    }
} // namespace hack::features::misc
