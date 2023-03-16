#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    void bhop(c_usercmd* cmd) {
        if (!opts::bhop)
            return;

        if (!(cmd->m_buttons & e_cmd_buttons::in_jump))
            return;

        if (portal::players::local->m_fFlags() & e_ent_flags::fl_onground)
            return;

        cmd->m_buttons &= ~e_cmd_buttons::in_jump;
    }
} // namespace hack::features::misc
